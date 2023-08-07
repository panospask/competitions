#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll, int> pi;

const int MAXLOG = 17;

int N, Q;
vector<int> dep;
vector<vector<int>> adj_list;
vector<int> ancestor[MAXLOG];
vector<ll> ans;
vector<pi> rm_inc;
vector<pi> rm_dec;
vector<pi> increasing;
vector<pi> decreasing;

vector<int> tin;
vector<int> tout;
int counter;

pi operator + (const pi& a, const pi& b)
{
    return mp(a.f + b.f, a.s + b.s);
}

pi operator - (const pi& a, const pi& b)
{
    return a + mp(-b.f, -b.s);
}

bool is_ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int jump(int v, int lvl)
{
    for (int up = 0; up < MAXLOG; up++)
        if ((1 << up) & lvl)
            v = ancestor[up][v];

    return v;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);

    a = jump(a, dep[a] - dep[b]);
    if (a == b)
        return a;

    for (int up = MAXLOG - 1; up >= 0; up--) {
        if (ancestor[up][a] != ancestor[up][b]) {
            a = ancestor[up][a];
            b = ancestor[up][b];
        }
    }

    return ancestor[0][a];
}

// From a up until b, where b is an ancestor of a
void process_query(int a, int b, int target)
{
    if (!is_ancestor(b, target)) {
        int dist = dep[b] + dep[target] - 2 * dep[lca(b, target)];

        // Initiate decreasing sequence from a to b
        decreasing[a].f += dist + dep[a] - dep[b];
        decreasing[a].s++;

        rm_dec[b].f += dist;
        rm_dec[b].s++;
    }
    else if (is_ancestor(a, target)) {
        int dist = dep[target] - dep[a];

        // Increasing from a to b
        increasing[a].f += dist;
        increasing[a].s++;

        rm_inc[b].f += dist + dep[a] - dep[b];
        rm_inc[b].s++;
    }
    else {
        // Find the first node on the path from b to a that is NOT an ancestor of t
        int l = 0;
        int r = dep[a] - dep[b];

        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (is_ancestor(jump(a, mid), target))
                r = mid;
            else
                l = mid;
        }

        int first = jump(a, l);
        int latest = ancestor[0][first];
        int dist = dep[target] - dep[latest] + 1;
        // Decreasing from a to first, increasing from first + 1 to b
        decreasing[a].f += dist + dep[a] - dep[first];
        decreasing[a].s++;

        rm_dec[first].f += dist;
        rm_dec[first].s++;

        dist--;
        increasing[latest].f += dist ;
        increasing[latest].s++;

        rm_inc[b].f += dist + dep[latest] - dep[b];
        rm_inc[b].s++;
    }
}

pair<pi, pi> calculate_answer(int node)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == ancestor[0][node])
            continue;

        auto res = calculate_answer(neigh);
        increasing[node] = increasing[node] + res.f;
        decreasing[node] = decreasing[node] + res.s;
    }

    ans[node] = increasing[node].f + decreasing[node].f;

    increasing[node] = increasing[node] - rm_inc[node];
    decreasing[node] = decreasing[node] - rm_dec[node];

    increasing[node].f += increasing[node].s;
    decreasing[node].f -= decreasing[node].s;

    return mp(increasing[node], decreasing[node]);
}

void init(int node)
{
    tin[node] = counter++;

    for (auto neigh : adj_list[node]) {
        if (neigh == ancestor[0][node])
            continue;

        ancestor[0][neigh] = node;
        dep[neigh] = dep[node] + 1;
        init(neigh);
    }

    tout[node] = counter;
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N);
        for (int i = 0; i < N; i++)
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    adj_list.resize(N);
    dep.resize(N);
    tin.resize(N);
    ans.resize(N);
    tout.resize(N);
    ancestor[0].resize(N);
    rm_dec.resize(N);
    rm_inc.resize(N);
    increasing.resize(N);
    decreasing.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dep[0] = 0;
    ancestor[0][0] = 0;
    init(0);

    calculate_ancestors();

    while (Q--) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);
        a--; b--; t--;

        if (dep[a] < dep[b])
            swap(a, b);

        if (a == b) {
            process_query(a, a, t);
        }
        else {
            int l = lca(a, b);
            int almost = jump(a, dep[a] - dep[l] - 1);

            process_query(b, l, t);
            process_query(a, almost, t);
        }
    }

    calculate_answer(0);

    for (int i = 0; i < N; i++)
        printf("%lld ", ans[i]);
    printf("\n");

    return 0;
}