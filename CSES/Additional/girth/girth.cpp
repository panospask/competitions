#include <bits/stdc++.h>
#define MAXN 2500
#define pb push_back

using namespace std;

int n, m;
vector<int> adj_list[MAXN + 2];
int dist[MAXN + 2];
int p[MAXN + 2];
int ans= INT_MAX;

void bfs(int source)
{
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;

    p[source] = -1;
    dist[source] = 0;
    queue<int> q;

    q.push(source);
    while (!q.empty()) {
        int node = q.front(); q.pop();

        for (auto neigh : adj_list[node]) {
            if (dist[neigh] > dist[node] + 1) {
                dist[neigh] = dist[node] + 1;
                p[neigh] = node;
                q.push(neigh);
            }
            else if (p[node] != neigh) {
                ans = min(ans, 1 + dist[neigh] + dist[node]);
            }
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    for (int i = 0; i < n; i++)
        bfs(i);

    if (ans == INT_MAX)
        ans = -1;

    printf("%d\n", ans);
    return 0;
}