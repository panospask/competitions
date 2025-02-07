#include <bits/stdc++.h>
#define mp make_pair
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define pb push_back

using namespace std;

const int MAXLOG = 19;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {
    int size;
    vector<int> tree;
    const int DEFAULT = 0;

    void init(int N) {
        size = 1;
        while (size < N) {
            size = 2 * size;
        }

        tree.assign(2 * size, DEFAULT);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
        return;
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return DEFAULT;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);
        return c1 + c2;
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
vector<int> w;
vector<vector<int>> adj_list;
vector<vector<int>> by_weight;
vector<int> tin, tout, trav, dep;
vector<vector<int>> ancestor;
int total = 0;
int counter = 0;

SegTree singles, doubles;

// nodes represented by tin[node]
set<int> nodes;

vector<int> winning;

int jump(int u, int s)
{
    for (int b = 0; b < MAXLOG; b++) {
        if (CHECK_BIT(s, b)) {
            u = ancestor[b][u];
        }
    }

    return u;
}

int lca(int u, int v)
{
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    u = jump(u, dep[u] - dep[v]);
    if (u == v) {
        return u;
    }

    for (int up = MAXLOG - 1; up >= 0; up--) {
        int n_u = ancestor[up][u];
        int n_v = ancestor[up][v];
        if (n_u != n_v) {
            u = n_u;
            v = n_v;
        }
    }

    return ancestor[0][u];
}

void precalculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

// Is the state without u and its subtree winning
bool wins(int u)
{
    int s = singles.calc(tin[u], tout[u]);
    int d = doubles.calc(tin[u], tout[u]);

    return total > s - d;
}

// Add u to the possible nodes
void update(int u)
{
    if (nodes.empty()) {
        return;
    }

    int v1 = -1;
    auto it1 = nodes.begin();
    if (*it1 >= tin[u]) {
        it1 = nodes.lower_bound(tout[u]);
    }
    if (it1 != nodes.end()) {
        v1 = trav[*it1];
    }

    int v2 = -1;
    auto it2 = nodes.end();
    it2--;
    if (*it2 < tout[u]) {
        it2 = nodes.lower_bound(tin[u]);
        if (it2 != nodes.begin()) {
            it2--;
            v2 = trav[*it2];
        }
    }
    else {
        v2 = trav[*it2];
    }

    int c = -1;
    if (v1 != -1 && v2 != -1) {
        c = lca(v1, v2);
    }
    else if (v1 != -1) {
        c = v1;
    }
    else if (v2 != -1) {
        c = v2;
    }

    if (c == -1) {
        return;
    }

    singles.add(tin[u], 1);
    singles.add(tin[c], 1);
    doubles.add(tin[lca(u, c)], 1);
    total++;
}

void dfs(int node, int par)
{
    ancestor[0][node] = par;
    trav[counter] = node;
    tin[node] = counter++;

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dep[neigh] = dep[node] + 1;
            dfs(neigh, node);
        }
    }

    tout[node] = counter;
}

bool fully_contained(int u)
{
    if (nodes.empty()) {
        return true;
    }

    return tin[u] <= *nodes.begin() && tout[u] > *nodes.rbegin();
}

void solve(void)
{
    scanf("%d", &N);

    w.resize(N);
    by_weight.assign(N, vector<int>());
    adj_list.assign(N, vector<int>());
    tin.resize(N);
    tout.resize(N);
    trav.resize(N);
    dep.resize(N);
    singles.init(N);
    doubles.init(N);
    ancestor.assign(MAXLOG, vector<int>(N, -1));
    winning.clear();
    nodes.clear();
    counter = total = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
        w[i]--;
        by_weight[w[i]].pb(i);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dep[0] = 0;
    dfs(0, 0);
    precalculate_ancestors();

    for (int v = N - 1; v >= 0; v--) {
        for (auto u : by_weight[v]) {
            if (wins(u) == false && !fully_contained(u)) {
                // The opponent cannot win when we remove the subtree of u
                winning.pb(u);
            }
        }

        for (auto u : by_weight[v]) {
            update(u);
        }
        for (auto u : by_weight[v]) {
            nodes.insert(tin[u]);
        }
    }

    sort(winning.begin(), winning.end());
    printf("%d", (int)winning.size());
    for (auto u : winning) {
        printf(" %d", u + 1);
    }
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}