#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

map<ii, int> nodenums;
vector<int> adj_list[2][MAXN + 2];
int dist[2][MAXN + 2];
int n;
int vertices = 0;

vector<ii> ttl_points;

bool ysort(ii& a, ii& b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

int bfs(int start, int target)
{
    for (int i = 0; i < vertices; i++)
        dist[0][i] = dist[1][i] = INT_MAX;

    dist[0][start] = dist[1][start] = 0;
    deque<ii> q;
    q.push_front(mp(start, 0));
    q.push_front(mp(start, 1));

    int dir, node;
    while (!q.empty()) {
        tie(node, dir) = q.front(); q.pop_front();

        for (auto neigh : adj_list[dir][node]) {
            if (dist[dir][neigh] > dist[dir][node]) {
                dist[dir][neigh] = dist[dir][node];
                q.push_front(mp(neigh, dir));
            }
        }

        if (dist[!dir][node] > dist[dir][node] + 1) {
            dist[!dir][node] = dist[dir][node] + 1;
            q.push_back(mp(node, !dir));
        }

        // printf("%d %d %d\n", node, dist[0][node], dist[1][node]);
    }

    return min(dist[0][target], dist[1][target]);
}

int main(void)
{
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);

    int x1, y1, x2, y2;
    scanf("%d %d %d %d %d", &n, &x1, &y1, &x2, &y2);
    nodenums[mp(x1, y1)] = 0;
    nodenums[mp(x2, y2)] = 1;
    vertices = 2;
    ttl_points.pb(mp(x1, y1));
    ttl_points.pb(mp(x2, y2));

    int x, y;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        nodenums[mp(x,y)] = vertices++;
        ttl_points.pb(mp(x,y));
    }

    // Sort by x-coord
    sort(ttl_points.begin(), ttl_points.end());
    for (int p = 1; p < ttl_points.size(); p++) {
        if (ttl_points[p].first == ttl_points[p-1].first) {
            // They have the same x-coordinate => can go from one to the other
            int n1 = nodenums[ttl_points[p]];
            int n2 = nodenums[ttl_points[p-1]];

            adj_list[0][n1].pb(n2);
            adj_list[0][n2].pb(n1);
        }
    }

    // Sort by y-coord
    sort(ttl_points.begin(), ttl_points.end(), ysort);
    for (int p = 1; p < ttl_points.size(); p++) {
        if (ttl_points[p].second == ttl_points[p-1].second) {
            // They have the same y-coordinate => can go from one to the other
            int n1 = nodenums[ttl_points[p]];
            int n2 = nodenums[ttl_points[p-1]];

            adj_list[1][n1].pb(n2);
            adj_list[1][n2].pb(n1);
        }
    }

    // We have assembled the graph, run bfs
    int ans = bfs(0, 1);
    if (ans == INT_MAX)
        ans = -1;
    // else 
        // ans--;

    printf("%d\n", ans);
    return 0;
}