#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n, k;
vector<vector<int>> adj_list;
vector<vector<int>> ancestor;
vector<int> ans;
vector<int> depth;
vector<ii> nodetime;
vector<int> s;
vector<int> e;
int counter = 0;

int jump(int a, int levels)
{
    for (int i = 0; i < 20; i++)
        if (levels & (1<<i))
            a = ancestor[i][a];

    return a;
}

int find_lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);

    a = jump(a, depth[a] - depth[b]);
    if (a == b)
        return a;

    for (int i = 20 - 1; i >= 0; i--) {
        int a_anc = ancestor[i][a];
        int b_anc = ancestor[i][b];
        if (a_anc != b_anc) {
            a = a_anc;
            b = b_anc;
        }
    }

    return ancestor[0][a];
}

void dfs(int node, int d)
{
    depth[node] = d;
    nodetime[node].first = counter++;
    for (auto neigh : adj_list[node])
        if (neigh != ancestor[0][node]) {
            ancestor[0][neigh] = node;
            dfs(neigh, d + 1);
        }
    nodetime[node].second = counter;
}

int upcoming_paths(int node)
{
    ans[node] = s[node] - e[node] / 2;
    for (auto neigh : adj_list[node])
        if (neigh != ancestor[0][node])
            ans[node] += upcoming_paths(neigh);

    return ans[node] - e[node] / 2;
}

int main(void)
{
    freopen("maxflow.in", "r", stdin);
    freopen("maxflow.out", "w", stdout);

    scanf("%d %d", &n, &k);
    adj_list.resize(n + 1);
    nodetime.resize(n + 1);
    s.resize(n + 1);
    e.resize(n + 1);
    depth.resize(n + 1);
    ans.resize(n + 1);
    ancestor.assign(20, vector<int>(n + 1));
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    ancestor[0][1] = 0;
    dfs(1, 0);

    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            ancestor[i][j] = ancestor[i-1][ancestor[i-1][j]];

    for (int q = 0; q < k; q++) {
        int a, b;
        scanf("%d %d", &a, &b);
        int lca = find_lca(a, b);
        s[a]++;
        s[b]++;
        e[lca]++;
        e[lca]++;
    }

    upcoming_paths(1);

    int m = 0;
    for (int i = 1; i <= n; i++)
        m = max(m, ans[i]);

    printf("%d\n", m);
    return 0;
}