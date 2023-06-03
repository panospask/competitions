#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, pi> plp;

const ll INF = 1e18;

int n, m;
vector<vector<pi>> adj_list;
vector<vector<bool>> visited;
vector<vector<ll>> d;

int main(void)
{
    scanf("%d %d", &n, &m);

    adj_list.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
    }

    d.assign(n, vector<ll>(2, INF));
    visited.assign(n, vector<bool>(2, false));
    priority_queue<plp, vector<plp>, greater<plp>> q;

    d[0][0] = 0;
    q.push(mp(0, mp(0, false)));

    while (!q.empty()) {
        int v;
        bool used;
        tie(v, used) = q.top().s;
        q.pop();

        if (visited[v][used])
            continue;

        visited[v][used] = true;
        if (d[v][used] == INF)
            break;

        for (auto e : adj_list[v]) {
            if (d[e.f][used] > d[v][used] + e.s) {
                d[e.f][used] = d[v][used] + e.s;
                q.push(mp(d[e.f][used], mp(e.f, used)));
            }

            if (!used) {
                if (d[e.f][true] > d[v][false] + e.s / 2) {
                    d[e.f][true] = d[v][false] + e.s / 2;
                    q.push(mp(d[e.f][true], mp(e.f, true)));
                }
            }
        }
    }

    printf("%lld\n", d[n - 1][true]);

    return 0;
}