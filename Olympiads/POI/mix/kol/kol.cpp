#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, ll> pi;

const int MAXUP = 18;
const ll INF = 1e16;
const int ROOT = 0;

struct Query {
    int u, v, c;

    int pos;
};

// Global variables
int N, R, Q;
vector<int> t;
vector<Query> queries;
vector<ll> ans;
vector<vector<int>> cuisines;

// Variables used for the input tree
vector<vector<pi>> big_list;
vector<int> big_dep;
vector<ll> dist;
vector<vector<pi>> big_ancestor;
vector<int> tin, tout;
int counter = 0 ;

// Variables for each of the compressed trees
vector<vector<pi>> compressed_ancestor;
vector<vector<pi>> compressed_list;
vector<int> compressed_dep;
vector<ll> closest;

int CURRENT = -1;

void dfs(int node, int par, vector<vector<pi>>& adj_list, vector<int>& dep, bool isbig)
{
    if (isbig) {
        tin[node] = counter++;
    }

    if (t[node] == CURRENT) {
        closest[node] = 0;
    }
    else {
        closest[node] = INF;
    }

    for (auto [neigh, c] : adj_list[node]) {
        if (neigh != par) {
            dep[neigh] = dep[node] + 1;
            dist[neigh] = dist[node] + c;

            dfs(neigh, node, adj_list, dep, isbig);

            closest[node] = min(closest[node], closest[neigh] + c);
        }
    }

    if (isbig) {
        tout[node] = counter;
    }
}

void reroot(int node, int par, vector<vector<pi>>& adj_list, vector<vector<pi>>& ancestor)
{
    for (auto [neigh, c] : adj_list[node]) {
        if (neigh != par) {
            closest[neigh] = min(closest[neigh], closest[node] + c);
            reroot(neigh, node, adj_list, ancestor);
        }
    }

    for (auto [neigh, c] : adj_list[node]) {
        if (neigh != par) {
            ancestor[0][neigh] = {node, min(closest[node], closest[neigh])};
        }
    }
}

pi jump(int a, int k, vector<vector<pi>>& ancestor)
{
    ll opt = closest[a];
    for (int up = 0; up < MAXUP; up++) {
        if (CHECK_BIT(k, up)) {
            opt = min(opt, ancestor[up][a].second);
            a = ancestor[up][a].first;
        }
    }

    return mp(a, opt);
}

pi lca(int a, int b, vector<int>& dep, vector<vector<pi>>& ancestor)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    ll opt = min(closest[a], closest[b]);
    tie(a, opt) = jump(a, dep[a] - dep[b], ancestor);
    opt = min(opt, closest[b]);
    if (a == b) {
        return mp(a, opt);
    }

    for (int up = MAXUP - 1; up >= 0; up--) {
        int n_a = ancestor[up][a].first;
        int n_b = ancestor[up][b].first;

        if (n_a != n_b) {
            opt = min(opt, ancestor[up][b].second);
            opt = min(opt, ancestor[up][a].second);
            a = n_a;
            b = n_b;
        }
    }
    opt = min(opt, ancestor[0][a].second);
    opt = min(opt, ancestor[0][b].second);
    a = ancestor[0][a].first;

    return mp(a, opt);
}

ll path(int a, int b) 
{
    return dist[a] + dist[b] - 2 * dist[lca(a, b, big_dep, big_ancestor).first];
}

void precalculate_ancestors(vector<int> nodes, vector<vector<pi>>& ancestor)
{
    if (nodes.empty()) {
        nodes.resize(N);
        for (int i = 0; i < N; i++) {
            nodes[i] = i;
        }
    }

    for (int up = 1; up < MAXUP; up++) {
        for (auto i : nodes) {
            ancestor[up][i].first = ancestor[up - 1][ancestor[up - 1][i].first].first;
            ancestor[up][i].second = min(ancestor[up - 1][i].second, ancestor[up - 1][ancestor[up - 1][i].first].second);
        }
    }
}

bool querysort(const Query& a, const Query& b)
{
    return a.c < b.c;
}

bool eulersort(const int& a, const int& b)
{
    return tin[a] < tin[b];
}

bool eulereq(const int& a, const int& b)
{
    return tin[a] == tin[b];
}

int main(void)
{
    scanf("%d %d", &N, &R);

    big_list.resize(N);
    big_dep.resize(N);
    tin.resize(N);
    tout.resize(N);
    t.resize(N);
    dist.resize(N);
    big_ancestor.resize(MAXUP, vector<pi>(N, {0, INF}));
    compressed_ancestor.resize(MAXUP, vector<pi>(N, {0, INF}));
    cuisines.resize(R);
    closest.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
        t[i]--;
        cuisines[t[i]].pb(i);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--;

        big_list[u].pb(mp(v, c));
        big_list[v].pb(mp(u, c));
    }

    scanf("%d", &Q);
    queries.resize(Q);
    ans.resize(Q);
    for (int q = 0; q < Q; q++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--; c--;

        queries[q] = {u, v, c, q};
    }
    sort(queries.begin(), queries.end(), querysort);


    // Build the input tree
    big_dep[ROOT] = dist[ROOT] = 0;
    dfs(ROOT, ROOT, big_list, big_dep, true);
    reroot(ROOT, ROOT, big_list, big_ancestor);
    precalculate_ancestors({}, big_ancestor);


    compressed_dep.resize(N);
    compressed_list.resize(N);
    int p = 0;
    for (int c = 0; c < R; c++) {
        vector<int> special = cuisines[c];
        special.pb(ROOT);
        int prv = p;
        CURRENT = c;

        while (p < Q && queries[p].c == c) {
            special.pb(queries[p].u);
            special.pb(queries[p].v);
            p++;
        }

        sort(special.begin(), special.end(), eulersort);
        special.resize(unique(special.begin(), special.end(), eulereq) - special.begin());

        int K = special.size();
        for (int i = 0; i < K - 1; i++) {
            special.pb(lca(special[i], special[i + 1], big_dep, big_ancestor).first);
        }

        sort(special.begin(), special.end(), eulersort);
        special.resize(unique(special.begin(), special.end(), eulereq) - special.begin());

        for (int i = 0; i < special.size() - 1; i++) {
            int u = special[i + 1];
            int v = lca(special[i], special[i + 1], big_dep, big_ancestor).first;

            ll d = dist[u] - dist[v];

            compressed_list[u].pb(mp(v, d));
            compressed_list[v].pb(mp(u, d));
        }

        compressed_dep[ROOT] = 0;
        dfs(ROOT, ROOT, compressed_list, compressed_dep, false);
        reroot(ROOT, ROOT, compressed_list, compressed_ancestor);
        precalculate_ancestors(special, compressed_ancestor);

        for (int q = prv; q < p; q++) {
            ans[queries[q].pos] = path(queries[q].u, queries[q].v) + 2 * lca(queries[q].u, queries[q].v, compressed_dep, compressed_ancestor).second;
        }

        for (int i = 0; i < special.size(); i++) {
            compressed_list[special[i]].clear();
            compressed_dep[special[i]] = 0;
        }
    }

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", ans[i] >= INF ? -1 : ans[i]);
    }

    return 0;
}