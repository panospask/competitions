#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int INF = 1e9 + 3;

int T, N;
vector<tuple<int, int, int>> edges;
vector<vector<int>> adj_list;
vector<int> dist;
vector<bool> visited;

void dfs(int node)
{
    visited[node] = true;
    for (auto neigh : adj_list[node]) {
        if (!visited[neigh]) {
            dfs(neigh);
        }
    }
}

void solve(void)
{
    edges.clear();
    visited.assign(N, false);
    adj_list.assign(N, vector<int>());
    dist.assign(N, INF);

    int M, j, v;
    for (int i = 0; i < N; i++) {
        scanf("%d", &M);

        for (int c = 0; c < M; c++) {
            scanf("%d %d", &j, &v);
            j--;

            edges.pb({j, i, v});
        }
    }

    // Bellman-ford to locate negative cycle in graph
    bool negcyc = false;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            // Make i source
            dfs(i);
            dist[i] = 0;
        }
    }

    for (int iter = 0; iter < N; iter++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == INF) {
                continue;
            }

            if (dist[v] > dist[u] + w) {
                dist[v] = max(-INF, dist[u] + w);
                negcyc = iter == N - 1;
            }
        }
    }

    if (negcyc) {
        printf("false\n");
    }
    else {
        printf("true\n");
    }

    return;
}

int main(void)
{
    freopen("nonneg.in", "r", stdin);
    freopen("nonneg.out", "w", stdout);

    scanf("%d %d", &T, &N);

    while (T--) {
        solve();
    }

    return 0;
}