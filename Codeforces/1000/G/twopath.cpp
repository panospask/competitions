#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int MAXLOG = 20;

typedef long long ll;
typedef pair<int, int> pi;

struct State {
    int top;
    ll val;
};

int N, Q;
vector<int> v;
vector<ll> best_subtree;
vector<ll> best_par;
vector<pi> par;
vector<int> dep;
vector<vector<pi>> adj_list;

vector<State> ancestor[MAXLOG];

State DEFAULT = {N, 0};

State merge(const State& a, const State& b)
{
    State c;
    c.top = b.top;
    c.val = a.val + b.val;
    c.val -= par[a.top].second;
    if (best_subtree[a.top] - 2 * par[a.top].second >= 0)
        c.val -= best_subtree[a.top] - 2 * par[a.top].second;

    return c;
}

State jump(int v, int lvl)
{
    State cur = DEFAULT;
    for (int up = 0; up < MAXLOG; up++)
        if ((1 << up) & lvl) {
            cur = merge(cur, ancestor[up][v]);
            v = par[cur.top].first;
        }

    return cur;
}

ll lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);

    State s1 = DEFAULT;
    State s2 = DEFAULT;
    if (dep[a] != dep[b]) {
        s1 = jump(a, dep[a] - dep[b]);
        a = s1.top;

        if (par[a].first == b) {
            s1 = merge(s1, ancestor[0][b]);
            ll res = s1.val + best_par[b];

            return res;
        }

        a = par[a].first;
    }

    for (int up = MAXLOG - 1; up >= 0; up--) {
        int n1 = par[ancestor[up][a].top].first;
        int n2 = par[ancestor[up][b].top].first;

        if (n1 != n2) {
            s1 = merge(s1, ancestor[up][a]);
            s2 = merge(s2, ancestor[up][b]);
            a = n1;
            b = n2;
        }
    }

    int L = par[a].first;
    s1 = merge(s1, ancestor[0][a]);
    s2 = merge(s2, ancestor[0][b]);

    ll res = s1.val + s2.val + best_par[L] + best_subtree[L] - par[a].second - par[b].second;
    if (best_subtree[a] - 2 * par[a].second >= 0)
        res -= best_subtree[a] - 2 * par[a].second;
    if (best_subtree[b] - 2 * par[b].second >= 0)
        res -= best_subtree[b] - 2 * par[b].second;

    return res;
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N + 1);
        for (int i = 0; i <= N; i++) {
            ancestor[up][i] = merge(ancestor[up - 1][i], ancestor[up - 1][par[ancestor[up - 1][i].top].first]);
        }
    }
}

void dfs(int node)
{
    best_subtree[node] = v[node];

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par[node].first)
            continue;

        par[neigh] = mp(node, w);
        dep[neigh] = dep[node] + 1;
        dfs(neigh);

        best_subtree[node] += max(0ll, best_subtree[neigh] - 2 * w);
    }
}

void calc_par(int node)
{
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par[node].first)
            continue;

        best_par[neigh] = best_par[node] + best_subtree[node] - max(0ll, best_subtree[neigh] - 2 * w);
        best_par[neigh] = max(best_par[neigh] - 2 * w, 0ll);
        calc_par(neigh);
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    DEFAULT.top = N;
    v.resize(N + 1);
    par.resize(N + 1);
    adj_list.resize(N);
    best_subtree.resize(N + 1);
    best_par.resize(N + 1);
    dep.resize(N + 1);

    for (int i = 0; i < N; i++)
        scanf("%d", &v[i]);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    dep[0] = 0;
    par[0] = mp(N, 0);
    par[N] = mp(N, 0);
    dfs(0);
    best_par[0] = 0;
    calc_par(0);

    ancestor[0].resize(N + 1);
    for (int i = 0; i < N; i++)
        ancestor[0][i] = {i, best_subtree[i]};
    ancestor[0][N] = DEFAULT;
    calculate_ancestors();

    while (Q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        ll ans = 0;
        if (u == v) {
            ans = best_subtree[v] + best_par[v];
        }
        else {
            ans = lca(u, v);
        }
        printf("%lld\n", ans);
    }

    return 0;
}