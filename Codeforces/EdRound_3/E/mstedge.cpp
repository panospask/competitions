#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

struct DSU {
    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rep.resize(size);
        rank.assign(size, 0);

        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (rep[a] != a) {
            rep[a] = find(rep[a]);
        }

        return rep[a];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (rank[a] < rank[b])
            swap(a, b);
        if (rank[a] == rank[b])
            rank[a]++;

        rep[b] = a;

        return true;
    }
};

struct Edge {
    int a, b, w, id;
    bool operator < (const Edge& a) {
        return this->w < a.w;
    }
};

typedef pair<int, int> pi;

const int MAXLOG = 20;

typedef long long ll;

int N, M;
DSU graph;
vector<vector<pi>> adj_list;
vector<Edge> edges;
vector<int> dep;
vector<bool> used;
vector<ll> ans;

vector<pi> ancestor[MAXLOG];

void dfs(int node)
{
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == ancestor[0][node].f)
            continue;

        dep[neigh] = dep[node] + 1;
        ancestor[0][neigh] = mp(node, w);
        dfs(neigh);
    }
}

void calculate_ancestor(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N + 1);
        for (int i = 0; i <= N; i++) {
            ancestor[up][i].f = ancestor[up - 1][ancestor[up - 1][i].f].f;
            ancestor[up][i].s = max(ancestor[up - 1][i].s, ancestor[up - 1][ancestor[up - 1][i].f].s);
        }
    }
}

pi jump(int a, int lvl)
{
    int emax = 0;
    for (int up = MAXLOG - 1; up >= 0; up--) {
        if ((1 << up) & lvl) {
            emax = max(emax, ancestor[up][a].s);
            a = ancestor[up][a].f;
        }
    }

    return mp(a, emax);
}

int min_edge(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);

    int emax;
    tie(a, emax) = jump(a, dep[a] - dep[b]);

    if (a == b)
        return emax;

    for (int up = MAXLOG - 1; up >= 0; up--) {
        int n_a = ancestor[up][a].f;
        int n_b = ancestor[up][b].f;

        if (n_a != n_b) {
            emax = max(emax, ancestor[up][a].s);
            emax = max(emax, ancestor[up][b].s);
            a = n_a;
            b = n_b;
        }
    }

    emax = max(emax, ancestor[0][a].s);
    emax = max(emax, ancestor[0][b].s);

    return emax;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    graph.init(N);
    adj_list.resize(N);
    edges.resize(M);
    dep.resize(N);
    ans.resize(M);

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        edges[i] = {u, v, w, i};
    }
    sort(edges.begin(), edges.end());
    used.assign(M, false);

    ll best = 0;
    for (auto e : edges) {
        if (graph.unite(e.a, e.b)) {
            best += e.w;
            used[e.id] = true;
            adj_list[e.a].pb(mp(e.b, e.w));
            adj_list[e.b].pb(mp(e.a, e.w));
        }
    }

    ancestor[0].resize(N + 1);
    ancestor[0][0] = mp(N, 0);
    ancestor[0][N] = mp(N, 0);
    dfs(0);

    calculate_ancestor();

    for (auto e : edges) {
        if (used[e.id])
            ans[e.id] = best;
        else
            ans[e.id] = best - min_edge(e.a, e.b) + e.w;
    }

    for (int i = 0; i < M; i++)
        printf("%lld\n", ans[i]);

    return 0;
}