#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

const ll INF = 1e18;

int n, m;
int S, T, U, V;
vector<vector<pi>> edges;
vector<vector<int>> kids_sp;
vector<bool> visited;
vector<vector<int>> par;
vector<int> indeg;
set<int> in_sp;


vector<ll> dp_f;
vector<ll> dp_b;

vector<ll> u_dist;
vector<ll> dist;

void calc_shortest_paths(int source, vector<ll>& dist, bool findpaths, int dest)
{
    dist.assign(n, INF);
    visited.assign(n, false);

    if (findpaths) {
        par.assign(n, vector<int>(0));
        kids_sp.resize(n);
    }

    priority_queue<pli, vector<pli>, greater<pli>> q;
    dist[source] = 0;
    q.push(mp(0, source));

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;
        if (dist[v] == INF)
            break;

        for (auto e : edges[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                q.push(mp(dist[e.f], e.f));

                if (findpaths)
                    par[e.f].clear();
            }

            if (findpaths && dist[e.f] == dist[v] + e.s)
                par[e.f].pb(v);
        }
    }

    if (findpaths) {
        visited.assign(n, false);
        indeg.assign(n, 0);
        queue<int> q;
        q.push(dest);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            if (visited[v])
                continue;
            visited[v] = true;
            in_sp.insert(v);

            for (auto p : par[v]) {
                kids_sp[p].pb(v);
                q.push(p);
            }

            indeg[v] = par[v].size();
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &S, &T, &U, &V);
    S--; T--; U--; V--;

    edges.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--;

        edges[u].pb(mp(v, c));
        edges[v].pb(mp(u, c));
    }

    calc_shortest_paths(S, dist, true, T);

    calc_shortest_paths(U, u_dist, false, -1);
    ll ans = u_dist[V];

    calc_shortest_paths(V, dist, false, -1);

    vector<int> curdeg = indeg;
    dp_f.assign(n, INF);
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        dp_f[v] = min(dist[v], dp_f[v]);

        for (auto kid : kids_sp[v]) {
            dp_f[kid] = min(dp_f[v], dp_f[kid]);
            curdeg[kid]--;
            if (curdeg[kid] == 0)
                q.push(kid);
        }
    }

    // Now go backwards
    // First calc degrees
    for (auto v : in_sp)
        for (auto p : par[v])
            curdeg[p]++;

    q.push(T);
    dp_b.assign(n, INF);
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        dp_b[v] = min(dist[v], dp_b[v]);

        for (auto p : par[v]) {
            dp_b[p] = min(dp_b[v], dp_b[p]);
            curdeg[p]--;
            if (curdeg[p] == 0)
                q.push(p);
        }
    }

    for (auto v : in_sp) {
        ans = min(ans, u_dist[v] + min(dp_f[v], dp_b[v]));
    }

    printf("%lld\n", ans);

    return 0;
}