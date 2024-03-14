#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

bool visited[MAXN + 5];
int colour[MAXN + 5];
int n, m;
vector<int> adj_list[MAXN + 5];
vector<int> nodes_colored[2];

void dfs(int node, bool col)
{
    if (visited[node])
        return;

    visited[node] = true;
    colour[node] = col;
    nodes_colored[col].pb(node);
    for (auto neigh : adj_list[node])
        dfs(neigh, !col);

    return;
}

void solve(void)
{
    memset(visited, false, sizeof(visited));

    nodes_colored[1].clear();
    nodes_colored[0].clear();
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        adj_list[i].clear();
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, 0);

    vector<int>* ans;
    if (nodes_colored[0].size() < nodes_colored[1].size())
        ans = &nodes_colored[0];    
    else    
        ans = &nodes_colored[1];

    printf("%d\n", (int)(*ans).size());
    for (auto node : *ans)
        printf("%d ", node + 1);
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}