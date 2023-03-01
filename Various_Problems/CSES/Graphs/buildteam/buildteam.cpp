#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

vector<int> adj_list[MAXN + 5];
int colour[MAXN + 5];
int par[MAXN + 5];
bool visited[MAXN + 5];
int n, m;

bool dfs(int node, int parent)
{
    if (visited[node]) {
        if (colour[node] == colour[parent])
            return false;
        else 
            return true;
    }

    par[node] = parent;
    colour[node] = !colour[parent];
    visited[node] = true;
    bool isgood = true;

    for (auto neigh : adj_list[node]) {
        isgood = isgood && dfs(neigh, node);
        if (!isgood) break;
    }

    return isgood;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    memset(colour, 0, sizeof(colour));
    memset(visited, 0, sizeof(visited));
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    bool isgood = true;
    for (int i = 0; i < n && isgood; i++)
        if (!visited[i]) {
            colour[i] = 0;
            isgood = dfs(i, i);
        } 

    if (!isgood)
        printf("IMPOSSIBLE\n");
    else {
        for (int i = 0; i < n; i++)
            printf("%d ", colour[i] + 1);
        printf("\n");
    }

    return 0;
}