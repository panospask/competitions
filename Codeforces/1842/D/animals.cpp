#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

const ll INF = 1e18 + 2;

int n, m;
vector<vector<pi>> adj_list;
vector<bool> visited;
vector<ll> dist;
vector<int> par;
vector<ll> patience;
vector<int> add_in_game;
vector<int> used;
vector<ll> game_time;

ll total_time = 0;

int next_find(void)
{
    ll minv = INF, min_i = -1;
    for (int i = 0; i < n; i++) {
        if (used[i])
            continue;

        if (minv > patience[i]) {
            min_i = i;
            minv = patience[i];
        }
    }

    return (int)min_i;
}

void dikjstra(int source)
{
    dist.assign(n, INF);
    par.assign(n, -1);
    visited.assign(n, false);
    dist[source] = 0;

    priority_queue<pli, vector<pli>, greater<pli>> q;
    q.push(mp(0, source));

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;

        for (auto e : adj_list[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                par[e.f] = v;
                q.push(mp(dist[e.f], e.f));
            }
        }
    }

    return;
}

void solve(void)
{
    dist.clear();
    adj_list.clear();
    par.clear();
    visited.clear();

    scanf("%d %d", &n, &m);

    adj_list.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;

        adj_list[a].pb(mp(b, w));
        adj_list[b].pb(mp(a, w));
    }

    dikjstra(0);

    if (dist[n - 1] == INF) {
        printf("inf\n");
        return;
    }

    patience.assign(n, INF);
    used.assign(n, false);
    patience[0] = 0;
    int latest_add = -1;
    while (latest_add != n - 1) {
        int v = next_find();

        total_time += patience[v];
        game_time.push_back(patience[v]);
        latest_add = v;
        used[v] = true;
        add_in_game.push_back(v);
        for (int i = 0; i < n; i++) {
            if (i != v)
                patience[i] -= patience[v];
        }

        for (auto neigh : adj_list[v])
            patience[neigh.f] = min(patience[neigh.f], (ll)neigh.s);

    }

    assert(total_time == dist[n - 1]);

    printf("%lld %d\n", total_time, (int)add_in_game.size() - 1);
    used.assign(n, false);
    for (int i = 0; i < add_in_game.size() - 1; i++) {
        used[add_in_game[i]] = true;
        for (int i = 0; i < n; i++)
            printf("%d", used[i]);
        printf(" %lld\n", game_time[i + 1]);
    }

    return;
}

int main(void)
{
    int t = 1;

    while (t--)
        solve();
}