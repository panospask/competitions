#include <bits/stdc++.h>
#define pb push_back

using namespace std;

struct SegTree {
    const int DEFAULT = 0;
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, DEFAULT);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) {
                tree[x] = a[lx];
            }
            else {
                tree[x] = DEFAULT;
            }

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return DEFAULT;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int m1 = calc(l, r, 2 * x + 1, lx, mid);
        int m2 = calc(l, r, 2 * x + 2, mid, rx);

        return max(m1, m2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N, Q;
vector<int> a;
vector<vector<int>> adj_list;
SegTree st;
vector<int> par;
vector<int> dep;
vector<int> head;
vector<int> id;
vector<int> initial;
vector<int> subtree_size;

int counter = 0;

int dfs(int node, int p)
{
    par[node] = p;
    subtree_size[node] = 1;
    dep[node] = (p != -1 ? dep[p] + 1 : 0);

    for (auto kid : adj_list[node]) {
        if (kid != par[node]) {
            subtree_size[node] += dfs(kid, node);
        }
    }

    return subtree_size[node];
}

void decompose(int node, int h)
{
    head[node] = h;
    id[node] = counter++;
    initial[id[node]] = a[node];

    int h_c = -1;
    int maxs = 0;
    for (auto kid : adj_list[node]) {
        if (kid != par[node] && subtree_size[kid] > maxs) {
            h_c = kid;
            maxs = subtree_size[kid];
        }
    }

    if (h_c != -1) {
        decompose(h_c, h);
    }

    for (auto kid : adj_list[node]) {
        if (kid != par[node] && kid != h_c) {
            decompose(kid, kid);
        }
    }
}

void update_value(int node, int v)
{
    st.set(id[node], v);
}

int calculate_path(int u, int v)
{
    int ans = 0;

    while (head[u] != head[v]) {
        if (dep[head[u]] > dep[head[v]]) {
            swap(u, v);
        }

        ans = max(ans, st.calc(id[head[v]], id[v] + 1));
        v = par[head[v]];
    }

    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    ans = max(ans, st.calc(id[u], id[v] + 1));

    return ans;
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    counter = 0;
    adj_list.resize(N);
    initial.resize(N);
    id.resize(N);
    par.resize(N);
    subtree_size.resize(N);
    dep.resize(N);
    head.resize(N);
    a.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    // dfs(0, -1);
    int ROOT = 0;
    dfs(ROOT, -1);
    decompose(ROOT, ROOT);
    st.init(N);
    st.build(initial);

    while (Q--) {
        int op, a, b;
        scanf("%d %d %d", &op, &a, &b);
        a--;

        if (op == 1) {
            update_value(a, b);
        }
        else {
            b--;
            printf("%d\n", calculate_path(a, b));
        }
    }

    return 0;
}