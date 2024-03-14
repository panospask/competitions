#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9;

int n;
vector<vector<int>> adj_list;
vector<int> subtree_size;
vector<int> centroid_p;
vector<bool> rm;
vector<ll> mindist;
vector<vector<int>> ancestor;
vector<int> depth;

void origin_dfs(int node, int par, int d)
{
    depth[node] = d;
    ancestor[0][node] = par;
    for (auto kid : adj_list[node])
        if (kid != par)
            origin_dfs(kid, node, d + 1);
}

int jump(int u, int levels)
{
    for (int i = 0; i < 20; i++)
        if (levels & (1<<i))
            u = ancestor[i][u];

    return u;
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        swap(u, v);

    u = jump(u, depth[u] - depth[v]);
    if (u == v)
        return u;

    for (int i = 19; i >= 0; i--) {
        int a_u = ancestor[i][u];
        int a_v = ancestor[i][v];
        if (a_u != a_v) {
            u = a_u;
            v = a_v;
        }
    }

    return ancestor[0][u];
}

int dist(int u, int v)
{
    int p = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[p];
}

int calc_subtree(int node, int par = -1)
{
    subtree_size[node] = 1;
    for (auto kid : adj_list[node])
        if (kid != par && !rm[kid])
            subtree_size[node] += calc_subtree(kid, node);

    return subtree_size[node];
}

int find_centroid(int node, int par, int treesize)
{
    for (auto kid : adj_list[node])
        if (kid != par && !rm[kid] && subtree_size[kid] * 2 > treesize)
            return find_centroid(kid, node, treesize);

    return node;
}

void decompose_centroid(int node, int par = -1)
{
    int cen = find_centroid(node, -1, calc_subtree(node));

    rm[cen] = true;
    centroid_p[cen] = par;
    for (auto kid : adj_list[cen]) {
        if (!rm[kid])
            decompose_centroid(kid, cen);
    }
}

void make_red(int node)
{
    for (int v = node; v != -1; v = centroid_p[v])
        mindist[v] = min(mindist[v], (ll)dist(node, v));
}

ll calc_dist(int node)
{
    ll res = INF;
    for (int v = node; v != -1; v = centroid_p[v])
        res = min(res, dist(node, v) + mindist[v]);

    return res;
}

int q;
int main(void)
{
    scanf("%d %d", &n, &q);
    adj_list.resize(n);
    ancestor.resize(20, vector<int>(n + 1));
    depth.resize(n);
    subtree_size.resize(n);
    rm.assign(n, false);
    centroid_p.assign(n, -1);
    mindist.assign(n, INF);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }
    origin_dfs(0, n, 0);
    ancestor[0][n] = n;
    for (int up = 1; up < 20; up++) {
        for (int i = 0; i < n; i++)
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
    }

    decompose_centroid(0);

    make_red(0);
    while (q--) {
        int op, v;
        scanf("%d %d", &op, &v);
        v--;
        if (op == 1)
            make_red(v);
        else
            printf("%lld\n", calc_dist(v));
    }

    return 0;
}