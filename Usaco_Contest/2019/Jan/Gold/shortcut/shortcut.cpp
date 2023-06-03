#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int INF = INT_MAX;

int n, m, t;

// SSSP variables
vector<vector<pi>> adj_list;
vector<int> dist;
vector<bool> visited;
vector<int> par;

// TopoSort variables
vector<int> indeg;
vector<int> total_use;

int main(void)
{
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &t);

    adj_list.resize(n);
    dist.assign(n, INF);
    par.assign(n, -1);
    visited.assign(n, false);
    indeg.assign(n, false);
    total_use.assign(n, 0);

    for (int i = 0; i < n; i++)
        scanf("%d", &total_use[i]);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }

    // Find shortest paths from 0 to all barns
    dist[0] = 0;
    par[0] = -1;

    priority_queue<pi, vector<pi>, greater<pi>> q;
    q.push(mp(0, 0));

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;

        if (par[v] != -1)
            indeg[par[v]]++;

        for (auto e : adj_list[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                par[e.f] = v;
                q.push(mp(dist[e.f], e.f));
            }
            else if (dist[e.f] == dist[v] + e.s && par[e.f] > v) {
                par[e.f] = v;
            }
        }
    }

    // Now find the total number of cows that will use this field
    queue<int> cur_proccess;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            cur_proccess.push(i);

    while (!cur_proccess.empty()) {
        int v = cur_proccess.front();
        cur_proccess.pop();
        
        if (v == 0)
            break;

        total_use[par[v]] += total_use[v];

        indeg[par[v]]--;
        if (indeg[par[v]] == 0)
            cur_proccess.push(par[v]);
    }

    // Examine each field to figure out where the max time save is
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll save = total_use[i] * (ll)(dist[i] - t);
        ans = max(ans, save);
    }

    printf("%lld\n", ans);
    return 0;
}