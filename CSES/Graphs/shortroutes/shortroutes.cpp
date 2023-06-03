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

int n, m;
vector<vector<pi>> adj_list;
vector<bool> visited;
vector<ll> d;

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

    d.assign(n, INF);
    visited.assign(n, false);
    priority_queue<pli, vector<pli>, greater<pli>> q;

    d[0] = 0;
    q.push(mp(0, 0));

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;

        visited[v] = true;
        if (d[v] == INF)
            break;

        for (auto edge : adj_list[v]) {
            if (d[edge.f] > d[v] + edge.s) {
                d[edge.f] = d[v] + edge.s;
                q.push(mp(d[edge.f], edge.f));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%lld ", d[i]);
    }
    printf("\n");

    return 0;
}