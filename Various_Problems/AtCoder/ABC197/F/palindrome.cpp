#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 1e9;
typedef pair<int, int> pi;
typedef pair<int, char> pc;

int N, M;
vector<vector<pc>> adj_list;

/* dist[i][j]:
 * The minimum number of steps required such that we can go from 0 to i and from
 * N-1 to j using edges of same letters
 */
vector<vector<int>> dist;
queue<pi> q;

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    dist.assign(N, vector<int>(N, INF));

    for (int i = 0; i < M; i++) {
        int u, v;
        char c;

        scanf("%d %d %c", &u, &v, &c);
        u--; v--;

        adj_list[u].pb(mp(v, c));
        adj_list[v].pb(mp(u, c));
    }

    q.push(mp(0, N - 1));
    dist[0][N - 1] = 0;
    int ans = INF;

    while (!q.empty()) {
        int u, v;
        tie(u, v) = q.front();
        q.pop();

        if (ans < dist[u][v]) {
            // We have found the optimal scenario
            break;
        }

        // Step 1: Check if u and v are the same node
        if (u == v) {
            ans = min(ans, dist[u][v]);
        }

        // Step 2: Check if u and v are neighbours
        for (auto [neigh, c] : adj_list[u]) {
            if (neigh == v) {
                ans = min(ans, dist[u][v] + 1);
            }
        }


        // Step 3: Unite neighbours of u with neighbours of v
        for (auto [n_u, c_u] : adj_list[u]) {
            for (auto [n_v, c_v] : adj_list[v]) {
                if (c_u == c_v && dist[n_u][n_v] == INF) {
                    dist[n_u][n_v] = dist[u][v] + 2;
                    q.push(mp(n_u, n_v));
                }
            }
        }
    }

    if (ans == INF) {
        ans = -1;
    }
    printf("%d\n", ans);

    return 0;
}