#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

const int MAXFLOW = 1001;
const int INF = 1e7;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<int, pi> pip;

int n, m;
vector<vector<pip>> adj_list;

// dist[i][k]: The minimum cost to create a pipe up to node with flow k
vector<vector<int>> dist;
vector<vector<bool>> visited;

int main(void)
{
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);

    scanf("%d %d", &n, &m);
    adj_list.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, c, k;
        scanf("%d %d %d %d", &u, &v, &c, &k);
        u--; v--;

        adj_list[u].pb(mp(v, mp(c, k)));
        adj_list[v].pb(mp(u, mp(c, k)));
    }

    dist.assign(n, vector<int>(MAXFLOW, INF));
    visited.assign(n, vector<bool>(MAXFLOW, false));
    priority_queue<pip, vector<pip>, greater<pip>> q;

    dist[0][MAXFLOW - 1] = 0;
    q.push(mp(0, mp(0, MAXFLOW - 1)));

    while (!q.empty()) {
        int v, flow;
        tie(v, flow) = q.top().s;
        q.pop();

        if (visited[v][flow])
            continue;
        visited[v][flow] = true;
        if (dist[v][flow] == INF)
            break;

        for (auto e : adj_list[v]) {
            int nflow = min(flow, e.s.s);

            if (dist[e.f][nflow] > dist[v][flow] + e.s.f) {
                dist[e.f][nflow] = dist[v][flow] + e.s.f;
                q.push(mp(dist[e.f][nflow], mp(e.f, nflow)));
            }
        }
    }

    double ans = 0;
    for (int flow = 1; flow < MAXFLOW; flow++)
        ans = max(ans, (double)flow / dist[n - 1][flow]);

    ll res = ans * 1e6;
    printf("%lld\n", res);

    return 0;
}