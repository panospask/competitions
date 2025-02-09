#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;
typedef pair<int, ll> pi;

const int MAXUP = 20;

int N, Q;
vector<int> t;
vector<vector<pi>> adj_list;
vector<vector<pi>> ancestor;
vector<int> dep;

// dp[node]: How much can you win when starting at node and going through its subtree
vector<ll> dp;

// outside[node]: How much can you win when starting at node(not include node) and going outside of the subtree
vector<ll> outside;

pi jump(int u, int dist)
{
    ll tips = 0;
    for (int up = 0; up < MAXUP; up++) {
        if (CHECK_BIT(dist, up)) {
            tips += ancestor[up][u].second;
            u = ancestor[up][u].first;
        }
    }

    return mp(u, tips);
}

ll calculate_path(int u, int v)
{
    if (dep[u] < dep[v]) {
        swap(u, v);
    }

    ll total = 0;
    tie(u, total) = jump(u, dep[u] - dep[v]);
    if (u == v) {
        return total + dp[u] + outside[u];
    }

    for (int up = MAXUP - 1; up >= 0; up--) {
        int n_u = ancestor[up][u].first;
        int n_v = ancestor[up][v].first;

        if (n_u != n_v) {
            total += ancestor[up][u].second + ancestor[up][v].second;
            u = n_u;
            v = n_v;
        }
    }

    total += ancestor[0][u].second + ancestor[0][v].second;
    int l = ancestor[0][u].first;
    total += outside[l] + dp[l];

    return total;
}

void precalculate_ancestors(void)
{
    for (int up = 1; up < MAXUP; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i].first = ancestor[up - 1][ancestor[up - 1][i].first].first;
            ancestor[up][i].second = ancestor[up - 1][i].second + ancestor[up - 1][ancestor[up - 1][i].first].second;
        }
    }
}

void dfs(int node, int par, int w_par)
{
    dp[node] = t[node];
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dep[neigh] = dep[node] + 1;
        dfs(neigh, node, w);
        dp[node] += max(dp[neigh] - 2 * w, 0LL);
    }

    ancestor[0][node].first = par;
    ancestor[0][node].second = (dp[node] - w_par) - max(dp[node] - 2 * w_par, 0LL);
}

void reroot(int node, int par, ll win)
{
    outside[node] = win;
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        ll cur = win + dp[node] - max(dp[neigh] - 2 * w, 0LL);
        reroot(neigh, node, cur);
    }
}

int main(void)
{
    freopen("tiphunting.in", "r", stdin);
    freopen("tiphunting.out", "w", stdout);

    int type;
    scanf("%d", &type);

    scanf("%d %d", &N, &Q);

    adj_list.resize(N);
    ancestor.assign(MAXUP, vector<pi>(N));
    dep.resize(N);
    dp.resize(N);
    outside.resize(N);
    t.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    dep[0] = 0;
    dfs(0, 0, 0);
    reroot(0, 0, 0);
    precalculate_ancestors();

    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;

        printf("%lld\n", calculate_path(l, r));
    }

    return 0;
}