#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;

const ll INF = 1e18;

struct Query {
    int v;
    bool l1, l2;
    int id;
};

int N, Q;
vector<vector<pair<int, pl>>> adj_list;
vector<vector<Query>> queries;
vector<ll> ans;

// connect[i]: Cost of the edge between the two versions of node i
vector<ll> connect;
vector<vector<vector<ll>>> dist;

vector<int> subtree;
vector<bool> removed;

void clear(vector<vector<ll>>& v)
{
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            v[i][j] = INF;
        }
    }
}

bool exists(int v, vector<int>& a)
{
    int pos = lower_bound(a.begin(), a.end(), v) - a.begin();
 
    return pos != a.size() && a[pos] == v;
}

void process(int u, vector<int>& a)
{
    for (auto [v, l1, l2, id] : queries[u]) {
        if (exists(v, a)) {
            ans[id] = min(ans[id], min(dist[u][l1][0] + dist[v][l2][0], dist[u][l1][1] + dist[v][l2][1]));
        }
    }
}

void dfs(int node, int par)
{
    subtree[node] = 1;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        clear(dist[neigh]);
        dfs(neigh, node);

        subtree[node] += subtree[neigh];
    }
}

void dijkstra(pi source, int p)
{
    priority_queue<pair<ll, pi>, vector<pair<ll, pi>>, greater<pair<ll, pi>>> q;

    dist[source.first][source.second][p] = 0;
    q.push({0, source});

    while (!q.empty()) {
        int u, l;
        ll d;

        auto cur = q.top();
        q.pop();

        tie(u, l) = cur.second;
        d = cur.first;

        if (dist[u][l][p] != d) {
            continue;
        }

        for (auto [v, w] : adj_list[u]) {
            if (removed[v]) {
                continue;
            }

            ll cost = l == 0 ? w.first : w.second;
            if (dist[v][l][p] > dist[u][l][p] + cost) {
                dist[v][l][p] = dist[u][l][p] + cost;
                q.push({dist[v][l][p], {v, l}});
            }
        }

        if (dist[u][!l][p] > dist[u][l][p] + connect[u]) {
            dist[u][!l][p] = dist[u][l][p] + connect[u];
            q.push({dist[u][!l][p], {u, !l}});
        }
    }
}

int find_centroid(int node, int par, int total)
{
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        if (subtree[neigh] > total / 2) {
            return find_centroid(neigh, node, total);
        }
    }

    return node;
}

void insert(int node, int par, vector<int>& l)
{
    l.push_back(node);

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par || removed[neigh]) {
            continue;
        }

        insert(neigh, node, l);
    }
}

void decompose(int node)
{
    node = find_centroid(node, -1, subtree[node]);

    clear(dist[node]);
    dfs(node, -1);
    dijkstra({node, 0}, 0);
    dijkstra({node, 1}, 1);

    removed[node] = true;

    vector<int> curnodes;
    curnodes.pb(node);
    for (auto [kid, w] : adj_list[node]) {
        if (!removed[kid]) {
            insert(kid, node, curnodes);
        }
    }

    sort(curnodes.begin(), curnodes.end());
    for (auto u : curnodes) {
        process(u, curnodes);
    }

    for (auto [kid, w] : adj_list[node]) {
        if (!removed[kid]) {
            decompose(kid);
        }
    }
}

int main(void)
{
    scanf("%d", &N);

    connect.resize(N);
    adj_list.resize(N);
    subtree.resize(N);
    dist.assign(N, vector<vector<ll>>(2, vector<ll>(2, INF)));
    removed.assign(N, false);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &connect[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        ll w1, w2;

        scanf("%d %d %lld %lld", &u, &v, &w1, &w2);
        u--; v--;

        adj_list[u].pb({v, {w1, w2}});
        adj_list[v].pb({u, {w1, w2}});
    }

    scanf("%d", &Q);

    queries.resize(N);
    ans.assign(Q, INF);
    for (int i = 0; i < Q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        int u = a / 2;
        int v = b / 2;
        bool l1 = a % 2;
        bool l2 = b % 2;

        queries[u].push_back({v, l1, l2, i});
    }

    dfs(0, -1);
    decompose(0);

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}