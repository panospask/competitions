#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))
#define pb push_back

using namespace std;

const int INF = 1e9;
const int MAXANC = 20;

int N, Q;
vector<vector<int>> adj_list;

// Calculate necessary distances in the tree
vector<vector<int>> ancestor;
vector<int> dep;

// Centroid tree
vector<int> centroid_par;
vector<bool> used;
vector<int> subtree_size;

// Colour related
vector<int> mindist;

void calculate_ancestor(void)
{
    for (int up = 1; up < MAXANC; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            ancestor[0][neigh] = node;
            dep[neigh] = dep[node] + 1;
            dfs(neigh, node);
        }
    }
}

int jump(int a, int d)
{
    for (int up = 0; up < MAXANC; up++) {
        if (CHECK_BIT(d, up)) {
            a = ancestor[up][a];
        }
    }

    return a;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }
    a = jump(a, dep[a] - dep[b]);
    if (a == b) {
        return a;
    }

    for (int up = MAXANC - 1; up >= 0; up--) {
        int n_a = ancestor[up][a];
        int n_b = ancestor[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestor[0][a];
}

int dist(int a, int b)
{
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

int calc_subtree_size(int node, int par)
{
    subtree_size[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh != par && !used[neigh]) {
            subtree_size[node] += calc_subtree_size(neigh, node);
        }
    }

    return subtree_size[node];
}

int find_centroid(int node, int par, int tot)
{
    for (auto kid : adj_list[node]) {
        if (kid != par && !used[kid] && subtree_size[kid] * 2 > tot) {
            return find_centroid(kid, node, tot);
        }
    }

    return node;
}

void centroid_decompose(int node, int par)
{
    int cen = find_centroid(node, -1, calc_subtree_size(node, -1));

    centroid_par[cen] = par;
    used[cen] = true;

    for (auto kid : adj_list[cen]) {
        if (!used[kid]) {
            centroid_decompose(kid, cen);
        }
    }
}

int find_closest(int node)
{
    int ans = INF;
    int p = node;

    while (p != -1) {
        ans = min(ans, mindist[p] + dist(p, node));
        p = centroid_par[p];
    }

    return ans;
}

void make_red(int node)
{
    int p = node;

    while (p != -1) {
        mindist[p] = min(mindist[p], dist(p, node));
        p = centroid_par[p];
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    used.assign(N, false);
    centroid_par.resize(N);
    adj_list.resize(N);
    ancestor.resize(MAXANC, vector<int>(N));
    mindist.assign(N, INF);
    dep.resize(N);
    subtree_size.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    // 0 is arbitrary root in the tree used for calculating distances
    ancestor[0][0] = 0;
    dfs(0, -1);
    calculate_ancestor();

    centroid_decompose(0, -1);

    make_red(0);
    while (Q--) {
        int op, x;
        scanf("%d %d", &op, &x);
        x--;

        if (op == 1) {
            make_red(x);
        }
        else {
            printf("%d\n", find_closest(x));
        }
    }

    return 0;
}