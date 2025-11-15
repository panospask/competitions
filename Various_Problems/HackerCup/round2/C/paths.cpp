#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int INF = 1e9;

int N, K, M;

vector<vector<int>> routes;
vector<vector<pi>> stations;

// True if route[i][j] was used somewhere as mere nothing
vector<vector<bool>> used;

vector<int> dist;

vector<bool> visited;

void solve(void) {
    scanf("%d %d %d", &N, &K, &M);
    
    stations.assign(N, vector<pi>());
    routes.assign(M, vector<int>());
    used.assign(M, vector<bool>());
    dist.assign(N, -1);
    visited.assign(N, false);

    for (int i = 0; i < M; i++) {
        int l;
        scanf("%d", &l);

        used[i].assign(l, false);
        routes[i].resize(l);

        for (int j = 0; j < l; j++) {
            scanf("%d", &routes[i][j]);
            
            routes[i][j]--;
            stations[routes[i][j]].pb({i, j});
        }
    }

    queue<int> q;
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (auto [i, j] : stations[u]) {
            if (used[i][j]) {
                // Does not make sense to start travel here
                continue;
            }

            used[i][j] = true;
            for (int k = j + 1; k < min(j + K, (int)routes[i].size()); k++) {
                if (used[i][k]) {
                    break;
                }

                used[i][k] = true;
                if (dist[routes[i][k]] == -1) {
                    dist[routes[i][k]] = dist[u] + 1;
                    q.push(routes[i][k]);
                }
            }
            if (j + K < routes[i].size() && dist[routes[i][j + K]] == -1) {
                dist[routes[i][j + K]] = dist[u] + 1;
                q.push(routes[i][j + K]);
            }

            // for (int k = j - 1; k > max(j - K, -1); k--) {
            //     if (used[i][k]) {
            //         break;
            //     }

            //     used[i][k] = true;
            //     if (dist[routes[i][k]] == -1) {
            //         dist[routes[i][k]] = dist[u] + 1;
            //         q.push(routes[i][k]);
            //     }
            // }
            // if (j - K >= 0 && dist[routes[i][j - K]] == -1) {
            //     dist[routes[i][j - K]] = dist[u] + 1;
            //     q.push(routes[i][j - K]);
            // }
        }
    }

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        ans += (ll)(i + 1) * dist[i];
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);
    
    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }

    return 0;
}