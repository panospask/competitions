#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int INF = 1e9;

struct Edge {
    int u, v, w;
};

int N, M;
vector<int> degree;
vector<Edge> edges;
vector<bool> open;
ll ans = 0;

// DSU (somewhat) implementation
vector<int> rep;
// Only true if something merged there
vector<int> used;

vector<int> cost;
vector<vector<int>> kids;

int find(int a) {
    if (rep[a] != a) {
        rep[a] = find(rep[a]);
    }

    return rep[a];
}

// Unite a and b with parent p
void unite(int a, int b, int p) {
    rep[a] = p;
    rep[b] = p;

    if (a == b) {
        // Don't do much
        kids[p].pb(a);
        open[p] = open[a];

        return;
    }

    kids[p].pb(a);
    kids[p].pb(b);

    used[p] = open[a] && open[b];
    open[p] = open[a] ^ open[b];
}

void dfs(int node, int opt) {
    opt = min(opt, cost[node]);

    if (used[node]) {
        ans += opt;
    }

    for (auto c : kids[node]) {
        dfs(c, opt);
    }
}

void solve(void) {
    scanf("%d %d", &N, &M);

    degree.assign(N, 0);
    edges.assign(M, {0, 0, 0});
    ans = 0;

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        degree[u]++;
        degree[v]++;
        ans += w;

        edges[i] = {u, v, w};
    }

    rep.assign(N + M, 0);
    used.assign(N + M, false);
    open.assign(N + M, false);
    cost.assign(N + M, INF);
    kids.assign(N + M, vector<int>());

    for (int i = 0; i < N + M; i++) {
        rep[i] = i;
    }

    for (int i = 0; i < N; i++) {
        if (degree[i] % 2 == 1) {
            open[i] = true;
        }
    }

    for (int e = 0; e < M; e++) {
        // Use this edge
        int u = find(edges[e].u);
        int v = find(edges[e].v);
        cost[N + e] = edges[e].w;

        unite(u, v, N + e);
    }

    // And now descend
    dfs(N + M - 1, INF);

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}