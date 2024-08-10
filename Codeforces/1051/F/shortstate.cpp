#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
typedef pair<int, int> pi;

const ll INF = 1e18;
const int MAXUP = 20;

int N, M, Q;
vector<vector<pi>> adj_list;
vector<int> dep;

// Variables for the special nodes (i.e those who have edges outside the tree)
int S;
vector<int> special;
vector<vector<ll>> dist;
vector<bool> is_special;

// Variables for pathfinding in the tree
int counter;
vector<vector<int>> ancestor;
vector<int> tin, tout;
vector<ll> pref;

void dijkstra(int source, vector<ll>& dist)
{
    priority_queue<pli, vector<pli>, greater<pli>> q;

    dist[source] = 0;
    q.push(mp(0, source));

    while (!q.empty()) {
        int u;
        ll d;

        tie(d, u) = q.top();
        q.pop();

        if (dist[u] != d) {
            continue;
        }

        for (auto [v, w] : adj_list[u]) {
            if (dist[v] > w + dist[u]) {
                dist[v] = w + dist[u];
                q.push(mp(dist[v], v));
            }
        }
    }
}

void dfs(int node, int par)
{
    ancestor[0][node] = par;
    
    tin[node] = counter++;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            pref[tin[node]] = w;
            continue;
        }

        if (dep[neigh] != -1) {
            if (dep[neigh] < dep[node] && !is_special[node]) {
                special.pb(node);
                is_special[node] = true;
                S++;
            }
            continue;
        }

        dep[neigh] = dep[node] + 1;
        dfs(neigh, node);
    }

    tout[node] = counter++;
    pref[tout[node]] = -pref[tin[node]];
}

void compute_ancestors(void)
{
    for (int up = 1; up < MAXUP; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

int jump(int a, int v)
{
    for (int up = 0; up < MAXUP; up++) {
        if (CHECK_BIT(v, up)) {
            a = ancestor[up][a];
        }
    }

    return a;
}

int lca(int a, int b)
{
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    a = jump(a, dep[a] - dep[b]);
    if (a == b) {
        return a;
    }

    for (int up = MAXUP - 1; up >= 0; up--) {
        int n_a = ancestor[up][a];
        int n_b = ancestor[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestor[0][a];
}

ll treedist(int a, int b)
{
    int l = lca(a, b);

    return pref[tin[a]] + pref[tin[b]] - 2 * pref[tin[l]];
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    dep.assign(N, -1);
    tout.resize(N);
    tin.resize(N);
    pref.assign(2 * N, 0);
    ancestor.resize(MAXUP, vector<int>(N));
    is_special.assign(N, false);

    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        u--; v--;

        adj_list[u].pb(mp(v, d));
        adj_list[v].pb(mp(u, d));
    }

    dep[0] = 0;
    dfs(0, 0);

    // Propagate pref
    for (int i = 1; i < 2 * N; i++) {
        pref[i] += pref[i - 1];
    }

    compute_ancestors();

    dist.assign(S, vector<ll>(N, INF));
    for (int i = 0; i < S; i++) {
        dijkstra(special[i], dist[i]);
    }

    scanf("%d", &Q);
    while (Q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        ll res = treedist(u, v);
        for (int i = 0; i < S; i++) {
            res = min(res, dist[i][u] + dist[i][v]);
        }

        printf("%lld\n", res);
    }

    return 0;
}