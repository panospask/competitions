#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

const int MAXLOG = 17;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e18;

struct Node {
    ll dist;
    ll val;
    int anc;
};

int N, S, Q, E;
vector<ll> shopdist;
vector<bool> isshop;
vector<Node> ancestor[MAXLOG];
vector<vector<pi>> adj_list;
vector<int> tin;
vector<int> tout;
vector<int> dep;
vector<pi> edges;
int counter;

void dfs(int node, int par)
{
    tin[node] = counter++;
    if (par != -1)
        dep[node] = dep[par] + 1;
    else
        dep[node] = 0;

    shopdist[node] = INF;
    if (isshop[node])
        shopdist[node] = 0;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            ancestor[0][node].dist = w;
            continue;
        }

        dfs(neigh, node);
        shopdist[node] = min(shopdist[node], shopdist[neigh] + w);
    }

    ancestor[0][node].val = shopdist[node];
    ancestor[0][node].anc = par;

    tout[node] = counter;
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N + 1);
        for (int i = 0; i < N; i++) {
            int u = ancestor[up - 1][i].anc;

            ancestor[up][i].anc = ancestor[up - 1][u].anc;
            ancestor[up][i].dist = ancestor[up - 1][i].dist + ancestor[up - 1][u].dist;
            ancestor[up][i].val = min(ancestor[up - 1][i].val, ancestor[up - 1][i].dist + ancestor[up - 1][u].val);
        }
    }
}

ll jump(int v, int lvl)
{
    ll ans = INF;
    ll dist = 0;
    for (int up = 0; up < MAXLOG; up++) {
        if (((1 << up) & lvl) == 0)
            continue;

        ans = min(ans, ancestor[up][v].val + dist);
        dist = dist + ancestor[up][v].dist;
        v = ancestor[up][v].anc;
    }

    return ans;
}

bool is_ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int main(void)
{
    scanf("%d %d %d %d", &N, &S, &Q, &E);
    E--;

    shopdist.resize(N);
    isshop.assign(N, false);
    adj_list.resize(N);
    tin.resize(N);
    tout.resize(N);
    dep.resize(N);

    ancestor[0].resize(N + 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
        edges.pb(mp(u, v));
    }

    for (int i = 0; i < S; i++) {
        int v;
        scanf("%d", &v);

        isshop[v - 1] = true;
    }

    dfs(E, -1);
    ancestor[0][E].anc = N;
    ancestor[0][N].anc = N;

    calculate_ancestors();

    for (int q = 0; q < Q; q++) {
        int I, R;
        scanf("%d %d", &I, &R);
        I--; R--;

        if (dep[edges[I].f] > dep[edges[I].s])
            swap(edges[I].f, edges[I].s);

        if (!is_ancestor(edges[I].s, R)) {
            printf("escaped\n");
        }
        else {
            ll v = jump(R, dep[R] - dep[edges[I].f]);
            if (v == INF)
                printf("oo\n");
            else
                printf("%lld\n", v);
        }
    }
}