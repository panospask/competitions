#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

const ll INF = 1e18;

int n, m, k;
vector<vector<pi>> adj_list;
vector<bool> visited;
vector<pi> haybeles;

vector<ll> barndist;
vector<ll> haydist;

void calculate_shortest_paths(vector<int>& sources, vector<ll>& dist)
{
    priority_queue<pli, vector<pli>, greater<pli>> q;
    visited.assign(n, false);

    for (auto src : sources) {
        q.push(mp(dist[src], src));
    }

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;

        for (auto e : adj_list[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                q.push(mp(dist[e.f], e.f));
            }
        }
    }
}

int main(void)
{
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &k);

    adj_list.resize(n);
    barndist.assign(n, INF);
    haydist.assign(n, INF);
    haybeles.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    for (int i = 0; i < k; i++) {
        scanf("%d %d", &haybeles[i].f, &haybeles[i].s);
        haybeles[i].f--;
    }

    barndist[n - 1] = 0;
    vector<int> src(1, n - 1);
    calculate_shortest_paths(src, barndist);

    src.clear();
    src.resize(k);
    for (int i = 0; i < k; i++) {
        src[i] = haybeles[i].f;
        haydist[src[i]] = barndist[src[i]] - haybeles[i].s;
    }

    calculate_shortest_paths(src, haydist);

    for (int i = 0; i < n - 1; i++) {
        int ans = barndist[i] >= haydist[i];
        printf("%d\n", ans);
    }

    return 0;
}