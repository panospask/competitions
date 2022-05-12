#include <bits/stdc++.h>

using namespace std;

long long int n, m, height[50005], roots[50005], used[100000] = {false}, total_trees;
vector<pair<long long int,long long int>> adj_list[50005];
pair<long long int, pair<long long int,long long int>> edges[100000];

long long int find_root(long long int a)
{
    if (roots[a] != a)
        roots[a] = find_root(roots[a]);
    
    return roots[a];
}

void join_trees(long long int a, long long int b)
{
    long long int root1 = find_root(a);
    long long int root2 = find_root(b);

    if (height[root1] > height[root2]) 
        roots[root2] = root1;
    else if (height[root2] > height[root1])
        roots[root1] = root2;
    else {
        roots[root2] = root1;
        height[root1]++;
    }
    total_trees--;
}

bool same_root(long long int a, long long int b)
{
    if (find_root(a) == find_root(b))
        return true;
    
    return false;
}

//Lowest common ancestor
long long int timer, up[50005][17], dp[50005][17], tin[50005], tout[50005], l;

void dfs(long long int vert, long long int par, long long int weight)
{
    tin[vert] = ++timer;
    up[vert][0] = par;
    dp[vert][0] = weight;

    for (long long int i = 1; i <= l; i++) {
        up[vert][i] = up[up[vert][i - 1]][i - 1];
        dp[vert][i] = max(dp[vert][i - 1], dp[up[vert][i - 1]][i - 1]);
    }

    for (auto u : adj_list[vert]) {
        if (u.first != par)
            dfs(u.first, vert, u.second);
    }

    tout[vert] = ++timer;
}

bool is_ancestor(long long int u, long long int v)
{
    if (tin[u] <= tin[v] && tout[u] >= tout[v])
        return true;
    
    return false;
}

long long int find_lowest_common_anc(long long int u, long long int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;

    for (long long int i = l; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }

    return up[u][0];
}

long long int max_edge_in_line(long long int vert, long long int par)
{
    long long int max_edge = 0;

    for (long long int i = l; i >=0; i--) {
        if (!is_ancestor(up[vert][i], par)) {
            max_edge = max(max_edge,  dp[vert][i]);
            vert = up[vert][i];
        }
    }

    return max(max_edge, dp[vert][0]);
}

long long int max_edge_in_cycle(long long int u, long long int v)
{
    long long int lca = find_lowest_common_anc(u, v);

    if (lca == v)
        return max_edge_in_line(u, v);
    if (lca == u)
        return max_edge_in_line(v, u);
    
    return max(max_edge_in_line(v, lca), max_edge_in_line(u, lca));
}

long long int mst(void)
{
    sort(edges, edges + m);

    long long int total_weight = 0;
    for (long long int i = 0; i < m && total_trees > 1; i++) {
        long long int v1 = edges[i].second.first, v2 = edges[i].second.second;

        if (!same_root(v1, v2)) {
            join_trees(v1, v2);
            total_weight += edges[i].first;
            used[i] = true;
            adj_list[v1].push_back(make_pair(v2, edges[i].first));
            adj_list[v2].push_back(make_pair(v1, edges[i].first));
        }
    }

    return total_weight;
}

void init(void)
{
    for (long long int i = 1; i <= n; i++) {
        roots[i] = i;
        height[i] = 0;
    }
    total_trees = n;
    
    l = ceil(log2(n));
}

int main(void)
{
    freopen("christmas.in", "r", stdin);
    freopen("christmas.out", "w", stdout);

    cin >> n >> m;

    init();

    for (long long int i = 0; i < m; i++) {
        scanf("%lld %lld %lld", &edges[i].second.first, &edges[i].second.second, &edges[i].first);
    }

    long long int min_weight = mst();
    dfs(1, 1, 0);

    long long int sec_min_weight = LONG_LONG_MAX;
    for (long long int i = 0; i < m; i++) {
        if (!used[i]){
            long long int v1 = edges[i].second.first, v2 = edges[i].second.second;

            long long int max_edge = max_edge_in_cycle(v1, v2);

            long long int cur_weight = (min_weight - max_edge) + edges[i].first;

            sec_min_weight = min(sec_min_weight, cur_weight);
        }
    }

    printf("%lld %lld\n", min_weight, sec_min_weight);
}