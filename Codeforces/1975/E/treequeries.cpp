#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))

using namespace std;

typedef pair<int, int> pi;

int MAXANC = 20;

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

int N, Q;
SegTree st;
set<int> leafs;
vector<vector<int>> adj_list;
vector<int> black_kids;
vector<bool> black;
vector<vector<int>> ancestor;
vector<int> tin, tout, dep;
int ttl_black = 0;
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

void euler(int node, int p)
{
    ancestor[0][node] = p;

    tin[node] = counter++;

    for (auto kid : adj_list[node]) {
        if (kid != p) {
            dep[kid] = dep[node] + 1;
            euler(kid, node);
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

void make_white(int node)
{
    black[node] = false;
    ttl_black--;
    st.add(tin[node], -1);
    st.add(tout[node], 1);

    if (ancestor[0][node] != node) {
        black_kids[ancestor[0][node]]--;
        if (black_kids[ancestor[0][node]] == 0 && black[ancestor[0][node]]) {
            leafs.insert(ancestor[0][node]);
        }
    }

    if (black_kids[node] == 0) {
        leafs.erase(node);
    }
}

void make_black(int node)
{
    black[node] = true;
    ttl_black++;
    st.add(tin[node], 1);
    st.add(tout[node], -1);

    if (ancestor[0][node] != node) {
        black_kids[ancestor[0][node]]++;
        if (black_kids[ancestor[0][node]] == 1 && black[ancestor[0][node]]) {
            leafs.erase(ancestor[0][node]);
        }
    }

    if (black_kids[node] == 0) {
        leafs.insert(node);
    }
}

bool form_chain(int u, int v)
{
    int l = lca(u, v);

    int pathblack = st.calc(tin[l], tin[u] + 1) + st.calc(tin[l] + 1, tin[v] + 1);
    int dist = dep[u] + dep[v] - 2 * dep[l];

    if (pathblack == ttl_black && pathblack == dist + 1) {
        return true;
    }
    else {
        return false;
    }
}

void clear(void)
{
    adj_list.clear();
    leafs.clear();
}

void answer_query(void)
{
    if (leafs.size() ==  0 || leafs.size() > 2) {
        printf("No\n");
        return;
    }

    int u = *leafs.begin();
    int v;
    if (leafs.size() == 2) {
        v = *leafs.rbegin();
        if (form_chain(u, v)) {
            printf("Yes\n");
            return;
        }
    }
    else {
        if (dep[u] >= ttl_black - 1) {
            int l = jump(u, ttl_black - 1);
            if (st.calc(tin[l], tin[u] + 1) == ttl_black) {
                printf("Yes\n");
                return;
            }
        }
    }

    printf("No\n");
}

void solve(void)
{
    clear();

    scanf("%d %d", &N, &Q);

    MAXANC = 20;
    adj_list.resize(N);
    tin.resize(N);
    tout.resize(N);
    counter = 0;
    ancestor.assign(MAXANC, vector<int>(N, 0));
    black.assign(N, false);
    ttl_black = 0;
    dep.assign(N, 0);
    black_kids.assign(N, 0);

    for (int i = 0; i < N; i++) {
        int c;
        scanf("%d", &c);
        if (c) {
            black[i] = true;
        }
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    ancestor[0][0] = 0;
    counter = 0;
    dep[0] = 0;
    euler(0, 0);
    calculate_ancestors();
    st.init(counter);

    for (int i = 0; i < N; i++) {
        if (black[i]) {
            make_black(i);
        }
    }

    while (Q--) {
        int u;
        scanf("%d", &u);
        u--;

        if (black[u]) {
            make_white(u);
        }
        else {
            make_black(u);
        }

        answer_query();
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }

    return 0;
}