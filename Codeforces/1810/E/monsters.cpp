#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

struct DSU {
    int size;
    vector<int> rep;
    vector<int> total;
    vector<priority_queue<pi, vector<pi>, greater<pi>>> neighbours;

    void init(int N, vector<vector<int>>& adj_list, vector<int>& costlist) {
        size = N;
        rep.resize(N);
        total.resize(N);
        neighbours.assign(N, priority_queue<pi, vector<pi>, greater<pi>>());

        for (int u = 0; u < N; u++) {
            rep[u] = u;
            total[u] = 1;
            for (auto v : adj_list[u]) {
                neighbours[u].push(mp(costlist[v], v));
            }
        }
    }

    int find(int u) {
        if (rep[u] != u) {
            rep[u] = find(rep[u]);
        }

        return rep[u];
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    // Unite u and v and keep u as representative
    void unite(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) {
            return;
        }

        rep[v] = u;
        total[u] += total[v];

        if (neighbours[v].size() > neighbours[u].size()) {
            swap(neighbours[v], neighbours[u]);
        }

        while (!neighbours[v].empty()) {
            neighbours[u].push(neighbours[v].top());
            neighbours[v].pop();
        }
    }
};

int N, M;
vector<int> a;
vector<vector<int>> adj_list;
vector<bool> visited;
DSU graph;

bool process(int u) {
    while (!graph.neighbours[u].empty()) {
        int v = graph.neighbours[u].top().second;
        
        if (a[v] > graph.total[u]) {
            break;
        }
        graph.neighbours[u].pop();

        graph.unite(u, v);
    }

    return graph.total[u] == N;
}

void solve(void) {
    scanf("%d %d", &N, &M);

    a.resize(N);
    adj_list.assign(N, vector<int>());
    visited.assign(N, false);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    graph.init(N, adj_list, a);

    bool ans = false;
    for (int i = 0; i < N; i++) {
        if (a[i] == 0) {
            ans = ans || process(graph.find(i));
        }
    }

    if (ans) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}