#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
vector<vector<int>> adj_list;
vector<int> rep;
vector<int> diam;
vector<int> visited;

int dfs(int node, int par) {
    visited[node] = true;

    int v1 = 0, v2 = 0;
    for (auto neigh : adj_list[node]) {
        if (!visited[neigh]) {
            int opt = dfs(neigh, node) + 1;
            if (opt > v1) {
                swap(opt, v1);
            }
            if (opt > v2) {
                swap(opt, v2);
            }

            diam[node] = max(diam[node], diam[neigh]);
            rep[neigh] = node;
        }
    }

    diam[node] = max(diam[node], v1 + v2);
    return v1;
}

int find(int a) {
    if (a == rep[a]) {
        return a;
    }
    return rep[a] = find(rep[a]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) {
        return;
    }

    int v1 = diam[a];
    int v2 = diam[b];
    int v3 = (diam[a] + 1) / 2 + (diam[b] + 1) / 2 + 1;

    diam[a] = max(v1, max(v2, v3));
    rep[b] = a;
}

int main(void) {
    scanf("%d %d %d", &N, &M, &Q);

    adj_list.resize(N);
    rep.resize(N);
    diam.resize(N);
    visited.assign(N, false);

    for (int i = 0; i < N; i++) {
        rep[i] = i;
        diam[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            dfs(i, i);
        }
    }

    while (Q--) {
        int id;
        scanf("%d", &id);

        if (id == 1) {
            int x;
            scanf("%d", &x);
            x--;

            printf("%d\n", diam[find(x)]);
        }
        else {
            int u, v;
            scanf("%d %d", &u, &v);
            u--; v--;

            unite(u, v);
        }
    }

    return 0;
}