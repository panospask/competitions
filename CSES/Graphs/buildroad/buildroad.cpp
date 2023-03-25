#include <bits/stdc++.h>
#define MAXN 100000
#define pb push_back

using namespace std;

vector<int> adj_list[MAXN + 10];
int n, m;
bool visited[MAXN + 10];

void dfs(int node)
{
    if (visited[node])
        return;

    visited[node] = true;
    for (auto neigh: adj_list[node])
        dfs(neigh);
}

int main(void)
{
    scanf("%d %d", &n, &m);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        --a; --b;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    int starting = -1;
    vector<int> nodes_add;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            if (starting == -1)
                starting = i + 1;
            else 
                nodes_add.pb(i + 1);
        }
    }

    printf("%d\n", (int)nodes_add.size());
    for (auto node : nodes_add) {
        printf("%d %d\n", starting, node);
    }
    return 0;
}