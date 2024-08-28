#include "closing.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct Option {
    int node;
    int cnt;
    ll cost;
};

vector<ll> dist[2];
bool operator < (const Option& a, const Option& b)
{
    if (a.cost * b.cnt == a.cnt * b.cost) {
        if (dist[0][a.node] == dist[0][b.node]) {
            return a.cnt < b.cnt;
        }
    }

    return a.cost * b.cnt > a.cnt * b.cost;
}

int N, X, Y;
ll K;
vector<vector<pi>> adj_list;
vector<int> stage;

// The path between X and Y
vector<int> path;
vector<bool> in_path;

void dfs(int node, int par, vector<ll>& dist, bool find)
{
    for (auto [neigh, w] : adj_list[node]) {
        if (neigh != par) {
            dist[neigh] = dist[node] + w;
            dfs(neigh, node, dist, find);

            if (find && in_path[neigh]) {
                in_path[node] = true;
                path.pb(node);
            }
        }
    }

    if (find && node == Y) {
        in_path[node] = true;
        path.pb(node);
    }
}

// Max score if X moves l left across the path and Y moves r right
int find_max(void)
{
    ll rem = K;

    stage.assign(N, 0);
    priority_queue<Option> q;
    int res = 0;
    

    for (auto u : path) {
        stage[u] = 1;
        res++;
        rem -= min(dist[0][u], dist[1][u]);

        q.push({u, 1, max(dist[0][u], dist[1][u]) - min(dist[0][u], dist[1][u])});
        for (auto [v, w] : adj_list[u]) {
            if (in_path[v]) {
                continue;
            }

            q.push({v, 1, min(dist[0][v], dist[1][v])});
        }
    }

    if (rem < 0) {
        return 0;
    }

    ll latest_solo = 0;
    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        int u = cur.node;

        if (cur.cnt + stage[u] > 2) {
            continue;
        }
        if (cur.cost > rem) {
            if (cur.cnt == 2) {
                if (rem + latest_solo >= cur.cost) {
                    rem = rem + latest_solo - cur.cost;
                    res++;
                    latest_solo = 0;
                }
            }
            continue;
        }

        res += cur.cnt;
        rem -= cur.cost;
        stage[u] += cur.cnt;

        if (cur.cnt == 1) {
            latest_solo = cur.cost;
        }
        if (stage[u] == 1) {
            q.push({u, 1, max(dist[0][u], dist[1][u]) - min(dist[0][u], dist[1][u])});
        }
        
        for (auto [v, w] : adj_list[u]) {
            if (in_path[v] || dist[0][u] > dist[0][v]) {
                continue;
            }

            if (stage[u] == 1 || cur.cnt == 2) {
                q.push({v, 1, min(dist[0][v], dist[1][v])});
            }
            if (stage[u] == 2) {
                q.push({v, 2, max(dist[0][v], dist[1][v])});
            }
        }
    }

    return res;
}

int only_first(void)
{
    ll rem = K;
    int res = 0;
    priority_queue<Option> q;
    vector<ll> mindist(N);
    vector<bool> used(N);

    for (int i = 0; i < N; i++) {
        mindist[i] = min(dist[0][i], dist[1][i]);
        used[i] = false;
    }

    q.push({X, 1, 0});
    q.push({Y, 1, 0});

    while (!q.empty()) {
        auto cur = q.top();
        q.pop();
        int u = cur.node;

        if (used[u]) {
            continue;
        }
        if (mindist[u] > rem) {
            break;
        }
        used[u] = true;
        res++;
        rem -= mindist[u];

        for (auto [v, w] : adj_list[u]) {
            if (mindist[v] != mindist[u] + w) {
                continue;
            }

            q.push({v, 1, mindist[v]});
        }
    }

    return res;
}

int max_score(int n, int x, int y, long long k, vector<int> U, vector<int> V, vector<int> W)
{
    N = n;
    X = x;
    Y = y;
    K = k;
    adj_list.clear();
    path.clear();
    adj_list.resize(N);
    dist[0].resize(N);
    dist[1].resize(N);
    in_path.assign(N, false);

    for (int i = 0; i < N - 1; i++) {
        adj_list[U[i]].pb(mp(V[i], W[i]));
        adj_list[V[i]].pb(mp(U[i], W[i]));
    }

    dist[0][X] = dist[1][Y] = 0;
    dfs(X, -1, dist[0], true);
    dfs(Y, -1, dist[1], false);

    int a1 = find_max();
    int a2 = only_first();

    return max(a1, a2);
}
