#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int MAXK = 20; 

int N, Q;
// anc[k][x] = ancestor(x, 2^k)
vector<vector<int>> anc;
vector<int> dep;
vector<vector<int>> adj_list;

int jump(int node, int d) {
    int res = node;
    for (int k = 0; k < MAXK; k++) {
        if (CHECK_BIT(d, k)) {
            res = anc[k][res];
        }
    }

    return res;
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    v = jump(v, dep[v] - dep[u]);
    if (v == u) {
        return u;
    }

    int cur_u = u;
    int cur_v = v;
    for (int k = MAXK - 1; k >= 0; k--) {
        int new_u = anc[k][cur_u];
        int new_v = anc[k][cur_v];

        if (new_u != new_v) {
            cur_u = new_u;
            cur_v = new_v;
        }
    }

    return anc[0][cur_u];
}

void dfs(int node, int par) {
    anc[0][node] = par;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dep[neigh] = dep[node] + 1;
        dfs(neigh, node);
    }
}

void calculate_all(void) {
    for (int k = 1; k < MAXK; k++) {
        for (int x = 0; x < N; x++) {
            anc[k][x] = anc[k - 1][anc[k - 1][x]];
        }
    }
}

int main(void) {
    scanf("%d %d", &N, &Q);

    adj_list.resize(N);
    dep.assign(N, 0);
    anc.resize(MAXK, vector<int>(N, 0));

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, 0);
    calculate_all();

    while (Q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        int l = lca(a, b);

        printf("%d\n", dep[a] + dep[b] - 2 * dep[l]);
    }

    return 0;
}