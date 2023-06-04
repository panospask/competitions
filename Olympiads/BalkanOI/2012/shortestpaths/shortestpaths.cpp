#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

struct Edge {
    int a, b;
    int w;
};

const ll INF = 1e18;

int n, m, S, T;
vector<Edge> edges;
vector<vector<pi>> adj_list;
vector<ll> dist;
vector<ll> rdist;
vector<int> par;
vector<vector<int>> kids;
vector<bool> visited;
vector<int> rep_level;
vector<int> rep;
vector<ll> ans;
map<pi, int> dist_between;

void assign_rep_levels(int node, int lvl, int r)
{
    if (rep_level[node] == -1) {
        rep_level[node] = lvl;
        rep[node] = r;
    }

    for (auto kid : kids[node])
        assign_rep_levels(kid, rep_level[node], rep[node]);
}

void calc_sssp(int source, priority_queue<pli, vector<pli>, greater<pli>>& q, vector<ll>& d, bool track)
{
    visited.assign(n, false);

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;

        if (track && par[v] != -1)
            kids[par[v]].pb(v);

        for (auto e : adj_list[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                q.push(mp(dist[e.f], e.f));

                if (track)
                    par[e.f] = v;
            }
        }
    }
}

int main(void)
{
    scanf("%d %d %d %d", &n, &m, &S, &T);
    S--; T--;

    rep.assign(n, -1);
    rep_level.assign(n, -1);
    edges.resize(m);
    adj_list.resize(n);
    kids.resize(n);
    visited.assign(n, false);
    par.assign(n, -1);
    rep.assign(n, -1);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
        edges[i] = {v, u, w};
        dist_between[mp(v, u)] = w;
        dist_between[mp(u, v)] = w;
    }

    dist.assign(n, INF);
    rdist.assign(n, INF);

    priority_queue<pli, vector<pli>, greater<pli>> q;
    priority_queue<pli, vector<pli>, greater<pli>> rq;

    int k;
    scanf("%d", &k);
    int prv = -1;
    for (int i = 0; i < k; i++) {
        int v;
        scanf("%d", &v);
        v--;
        rep_level[v] = i;
        rep[v] = v;

        if (prv == -1) {
            dist[v] = 0;
        }
        else {
            // Find edge
            int w = -1;
            w = dist_between[mp(v, prv)];

            rdist[prv] = w;
            dist[v] = dist[prv] + w;
            kids[prv].pb(v);
        }
        q.push(mp(dist[v], v));

        par[v] = prv;
        prv = v;
    }
    prv = -1;
    for (int v = T; v != -1; v = par[v]) {
        if (prv == -1)
            rdist[v] = 0;
        else
            rdist[v] += rdist[prv];

        rq.push(mp(rdist[v], v));
        prv= v;
    }

    calc_sssp(S, q, dist, true);
    calc_sssp(T, rq, rdist, false);

    ans.assign(k, INF);
    assign_rep_levels(S, 0, 0);

    for (auto& e : edges) {
        if (rep_level[e.a] == INF || rep_level[e.b] == INF)
            continue;
        if (rep_level[e.a] > rep_level[e.b])
            swap(e.a, e.b);
        if (rep[e.a] == rep[e.b])
            continue;
        if (par[e.b] == e.a)
            continue;

        for (int j = rep_level[e.a]; j != rep_level[e.b]; j++)
            ans[j] = min(ans[j], dist[e.a] + rdist[e.b] + e.w);

    }

    for (int i = 0; i < k - 1; i++) {
        if (ans[i] == INF)
            printf("-1\n");
        else
            printf("%lld\n", ans[i]);
    }
}