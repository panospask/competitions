#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))

using namespace std;

const int MAXANC = 20;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);

        return c1 + c2;
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, M, K;
SegTree st;
vector<vector<int>> ancestor;
vector<bool> rem;
vector<vector<int>> adj_list;
vector<int> tin, tout, dep;
int counter;

int jump(int a, int v)
{
    for (int up = 0; up < MAXANC; up++) {
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

    for (int up = MAXANC - 1; up >= 0; up --) {
        int n_a = ancestor[up][a];
        int n_b = ancestor[up][b];

        if (n_a != n_b) {
            a = n_a;
            b = n_b;
        }
    }

    return ancestor[0][a];
}

void dfs(int node, int par)
{
    ancestor[0][node] = par;
    dep[node] = (par != node ? dep[par] + 1 : 0);

    tin[node] = counter++;

    for (auto kid : adj_list[node]) {
        if (kid != par) {
            dfs(kid, node);
        }
    }

    tout[node] = counter++;
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXANC; up++) {
        for (int i = 0; i < N; i++) {
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
        }
    }
}

void cut_road(int u, int v)
{
    if (ancestor[0][v] != u) {
        swap(u, v);
    }
    if (ancestor[0][v] != u) {
        return;
    }
    if (rem[v]) {
        return;
    }

    rem[v] = true;
    st.add(tin[v], 1);
    st.add(tout[v], -1);
}

int check_connectivity(int u, int v)
{
    int l = lca(u, v);

    if (st.calc(tin[l] + 1, tin[u] + 1) || st.calc(tin[l] + 1, tin[v] + 1)) {
        return 0;
    }
    else {
        return 1;
    }
}

int main(void)
{
    freopen("secretpaths.in", "r", stdin);
    freopen("secretpaths.out", "w", stdout);

    scanf("%d %d %d", &N, &M, &K);

    adj_list.resize(N);
    st.init(2 * N - 1);
    counter = 0;
    tin.resize(N);
    tout.resize(N);
    rem.assign(N, false);
    dep.resize(N);
    ancestor.resize(MAXANC, vector<int>(N));

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    ancestor[0][0] = 0;
    dfs(0, 0);
    calculate_ancestors();

    int s = 0;
    for (int i = 0; i < M; i++) {
        char c;
        int u, v;
        scanf(" %c %d %d", &c, &u, &v);
        u--; v--;
        int t = c == 'A';

        if (s ^ t) {
            cut_road(u, v);
        }
        else {
            int ans = check_connectivity(u, v);

            if (ans) {
                s = s ^ K;
                printf("yes\n");
            }
            else {
                printf("no\n");
            }
        }
    }

    return 0;
}