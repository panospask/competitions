#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 500
#define MAXM 500

using namespace std;

struct edge {
    int i, j, abs;

    edge(int a, int b, int c) {
        i = a;
        j = b;
        abs = c;
    }
};
typedef struct edge Edge;

int tiles[MAXN + 5][MAXM + 5];
int iswaypoint[MAXN + 5][MAXN + 5];
bool visited[MAXN + 5][MAXN + 5];
vector<Edge> adj_list[MAXN + 5][MAXN + 5];
int n, m;
int ttl_points;
int maxheight, minheight = INT_MAX;

int dfs(int i, int j, int d)
{
    if (visited[i][j])
        return 0;

    visited[i][j] = true;
    int waypoints = iswaypoint[i][j];
    for (auto& neigh : adj_list[i][j])
        if (neigh.abs <= d && !visited[neigh.i][neigh.j])
            waypoints += dfs(neigh.i, neigh.j, d);

    return waypoints;
}

bool can_reach(int d)
{
    memset(visited, false, sizeof(visited));
    return dfs(0, 0, d) == ttl_points;
}

int main(void)
{
    freopen("ccski.in", "r", stdin);
    freopen("ccski.out", "w", stdout);

    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &tiles[i][j]);
            minheight = min(minheight, tiles[i][j]);
            maxheight = max(maxheight, tiles[i][j]);
        }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            if (i != 0) {
                adj_list[i][j].pb(Edge(i - 1, j, abs(tiles[i][j] - tiles[i-1][j])));
            }
            if (i != m - 1) {
                adj_list[i][j].pb(Edge(i + 1, j, abs(tiles[i][j] - tiles[i+1][j])));
            }
            if (j != 0) {
                adj_list[i][j].pb(Edge(i, j - 1, abs(tiles[i][j] - tiles[i][j-1])));
            }
            if (j != n - 1) {
                adj_list[i][j].pb(Edge(i, j + 1, abs(tiles[i][j] - tiles[i][j+1])));
            }
        }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &iswaypoint[i][j]);
            if (iswaypoint[i][j])
                ttl_points++;
        }

    int l = -1; //can_reach(l) = false;
    int r = maxheight - minheight; //can_reach(r) = true
    while (r > l + 1) {
        auto mid = (r + l) / 2;
        if (can_reach(mid))
            r = mid;
        else 
            l = mid;
    }

    printf("%d\n", r);
    return 0;
}