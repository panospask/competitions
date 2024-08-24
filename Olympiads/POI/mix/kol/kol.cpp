#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, ll> pi;

const int MAXUP = 18;
const int CUT = 333;
const ll INF = 1e15;

struct Query {
    int u, v, c;

    int pos;
};

int N, R, Q;
vector<vector<pi>> adj_list;
vector<int> t;
vector<Query> queries;
vector<ll> ans;

vector<vector<int>> cuisines;
vector<int> id;
vector<int> heavy;

// Distance of a vertex from the source(0)
vector<ll> dist;
vector<int> dep;
vector<vector<pi>> ancestor;
vector<ll> closest;

int CURRENT = -1;

void dfs(int node, int par)
{
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
            dfs(neigh, node);

            closest[node] = min(closest[node], closest[neigh] + c);
        }
    }

}

void reroot(int node, int par)
{
    for (auto [neigh, c] : adj_list[node]) {
        if (neigh != par) {
            closest[neigh] = min(closest[neigh], closest[node] + c);
            reroot(neigh, node);
        }
    }

    for (auto [neigh, c] : adj_list[node]) {
        if (neigh != par) {
            ancestor[0][neigh] = {node, min(closest[node], closest[neigh])};
        }
    }
}

pi jump(int a, int k)
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

pi lca(int a, int b)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    ll opt = min(closest[a], closest[b]);
    tie(a, opt) = jump(a, dep[a] - dep[b]);
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
    return dist[a] + dist[b] - 2 * dist[lca(a, b).first];
}

void precalculate_ancestors(void)
{
    for (int up = 1; up < MAXUP; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i].first = ancestor[up - 1][ancestor[up - 1][i].first].first;
            ancestor[up][i].second = min(ancestor[up - 1][i].second, ancestor[up - 1][ancestor[up - 1][i].first].second);
        }
    }
}

bool querysort(const Query& a, const Query& b)
{
    return id[a.c] < id[b.c];
}

int main(void)
{
    scanf("%d %d", &N, &R);

    adj_list.resize(N);
    t.resize(N);
    dist.resize(N);
    dep.resize(N);
    ancestor.resize(MAXUP, vector<pi>(N, {0, INF}));
    closest.assign(N, INF);
    cuisines.resize(R);
    id.assign(N, -1);
    heavy.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
        t[i]--;
        cuisines[t[i]].pb(i);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--;

        adj_list[u].pb(mp(v, c));
        adj_list[v].pb(mp(u, c));
    }

    for (int c = 0; c < R; c++) {
        if (cuisines[c].size() > CUT) {
            id[c] = heavy.size();
            heavy.pb(c);
        }
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

    int ptr = 0;
    CURRENT = -1;
    dfs(0, 0);
    reroot(0, 0);
    precalculate_ancestors();
    while (ptr < Q && id[queries[ptr].c] == -1) {
        Query cur = queries[ptr];

        ans[cur.pos] = INF;
        for (auto node : cuisines[cur.c]) {
            ans[cur.pos] = min(ans[cur.pos], path(cur.u, node) + path(cur.v, node));
        }

        ptr++;
    }
    while (ptr < Q) {
        CURRENT = queries[ptr].c;

        dfs(0, 0);
        reroot(0, 0);
        ancestor[0][0] = {0, INF};
        precalculate_ancestors();

        while (ptr < Q && queries[ptr].c == CURRENT) {
            Query cur = queries[ptr];

            pi l = lca(cur.u, cur.v);
            ans[cur.pos] = dist[cur.u] + dist[cur.v] - 2 * dist[l.first] + 2 * l.second;

            ptr++;
        }
    }

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", ans[i] < INF ? ans[i] : -1);
    }

    return 0;
}