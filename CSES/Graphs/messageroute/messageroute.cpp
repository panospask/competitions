#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, m;
vector<int> adj_list[MAXN + 2];
int dist[MAXN + 2];
int par[MAXN + 2];
bool visited[MAXN + 2];

int bfs(int start, int target)
{
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    queue<int> q;
    dist[start] = 1;
    par[start] = -1;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int curnode = q.front(); q.pop();
        if (curnode == target)
            break;

        for (auto neigh : adj_list[curnode]) {
            if (!visited[neigh]) {
                dist[neigh] = dist[curnode] + 1;
                visited[neigh] = true;
                par[neigh] = curnode;
                q.push(neigh);
            }
        }
    }

    return dist[target];
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    int ans = bfs(0, n-1);
    if (ans == INT_MAX) {
        printf("IMPOSSIBLE\n");
        exit(EXIT_SUCCESS);
    }

    printf("%d\n", ans);
    vector<int> path;
    int node = n-1;
    while (node != -1) {
        path.push_back(node);
        node = par[node];
    }

    reverse(path.begin(), path.end());
    for (auto node : path) {
        printf("%d ", node + 1);
    }
    printf("\n");

    return 0;
}