#include <bits/stdc++.h>
#define pb push_back

using namespace std;

#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)

const int MAXUP = 20;

int N, Q;
vector<vector<int>> adj_list;

// ancestor[up][i]: Ancestor of i in level 2^up
vector<vector<int>> ancestor;
vector<int> dep;

int jump(int a, int v) {
    for (int up = 0; up < MAXUP; up++) {
        if (CHECK_BIT(v, up)) {
            a = ancestor[up][a];
        }
    }

    return a;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) {
        swap(a, b);
    }

    a = jump(a, dep[a] - dep[b]);
    if (a == b) {
        return a;
    }

    for (int up = MAXUP - 1; up >= 0; up--) {
        int na = ancestor[up][a];
        int nb = ancestor[up][b];

        if (na != nb) {
            a = na;
            b = nb;
        }
    }

    return ancestor[0][a];
}

void precalculate(void) {
    for (int up = 1; up < MAXUP; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

void dfs(int node, int par) {
    dep[node] = (node == 0) ? 0 : dep[par] + 1;
    ancestor[0][node] = par;

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dfs(neigh, node);
        }
    }
}

int main(void) {
    scanf("%d %d", &N, &Q);

    adj_list.assign(N, vector<int>());
    dep.resize(N);
    ancestor.assign(MAXUP, vector<int>(N, 0));
    for (int i = 1; i < N; i++) {
        int v;
        scanf("%d", &v);
        v--;

        adj_list[i].pb(v);
        adj_list[v].pb(i);
    }

    dfs(0, 0);
    precalculate();

    while (Q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        printf("%d\n", lca(u, v) + 1);
    }

    return 0;
}