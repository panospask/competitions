#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, pi> plp;

const ll INF = 1e18;

int n, m, k;
vector<vector<pi>> adj_list;
vector<vector<ll>> dist;
vector<vector<bool>> visited;

int main(void)
{
    scanf("%d %d %d", &n, &m, &k);

    adj_list.resize(n);
    dist.assign(n, vector<ll>(k, INF));
    visited.assign(n, vector<bool>(k, false));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
    }

    priority_queue<plp, vector<plp>, greater<plp>> q;
    dist[0][0] = 0;
    q.push(mp(0, mp(0, 0)));

    while (!q.empty()) {
        int v, num;
        tie(v, num) = q.top().s;
        q.pop();

        if (visited[v][num])
            continue;
        visited[v][num] = true;
        if (dist[v][num] == INF)
            break;

        for (auto e : adj_list[v]) {
            for (int n2 = num; n2 < k; n2++) {
                if (dist[e.f][n2] > dist[v][num] + e.s) {

                    // Iterate all distances with ind higher than num
                    for (int i = k - 1; i > n2; i--) {
                        if (dist[e.f][i] == dist[e.f][i - 1])
                            continue;

                        dist[e.f][i] = dist[e.f][i - 1];
                        q.push(mp(dist[e.f][i], mp(e.f, i)));
                    }
                    dist[e.f][n2] = dist[v][num] + e.s;
                    q.push(mp(dist[e.f][n2], mp(e.f, n2)));

                    break;
                }
            }
        }
    }

    for (int num = 0; num < k; num++)
        printf("%lld ", dist[n - 1][num]);
    printf("\n");

    return 0;
}