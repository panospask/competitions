#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int DEF = 1e9;

int N, M;

queue<int> q;
vector<int> dist;
vector<vector<int>> adj_list;

int main(void)
{
    freopen("publib.in", "r", stdin);
    freopen("publib.out", "w", stdout);

    scanf("%d %d", &N, &M);

    adj_list.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    int ans = DEF;

    for (int i = 0; i < N; i++) {
        dist.assign(N, DEF);
        dist[i] = 0;
        q.push(i);

        int maxdist = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            maxdist = max(maxdist, dist[v]);

            for (auto u : adj_list[v]) {
                if (dist[u] != DEF) {
                    continue;
                }

                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }

        ans = min(ans, maxdist);
    }

    printf("%d\n", ans);

    return 0;
}