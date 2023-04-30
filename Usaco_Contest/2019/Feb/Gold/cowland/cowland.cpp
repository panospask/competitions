#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int merge(int a, int b)
{
    return a ^ b;
}

struct SegmentTree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r)
            return 0;
        else if (l <= lx && rx <= r)
            return tree[x];

        int mid = (lx + rx) / 2;
        auto v1 = get(l, r, 2 * x + 1, lx, mid);
        auto v2 = get(l, r, 2 * x + 2, mid, rx);

        return merge(v1, v2);
    }
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int n, q;
vector<int> head;
SegmentTree st;
vector<int> id;
vector<int> depth;
vector<int> sz;
vector<int> p;
vector<int> v;
vector<vector<int>> adj_list;
int counter = 0;

void dfs(int node, int par, int d)
{
    p[node] = par;
    depth[node] = d;
    sz[node] = 1;

    for (auto kid : adj_list[node]) {
        if (kid != par) {
            dfs(kid, node, d + 1);
            sz[node] += sz[kid];
        }
    }
}

void decompose(int node, int par, int h)
{
    id[node] = counter++;
    st.set(id[node], v[node]);
    head[node] = h;

    int h_v = 0, h_c = -1;
    for (auto kid : adj_list[node]) {
        if (kid != par && sz[kid] > h_v) {
            h_c = kid;
            h_v = sz[h_c];
        }
    }

    if (h_c != -1)
        decompose(h_c, node, h);

    for (auto kid : adj_list[node])
        if (kid != par && kid != h_c)
            decompose(kid, node, kid);

    return;
}

void update_attraction(int x, int v)
{
    st.set(id[x], v);
}

int path(int a, int b)
{
    int res = 0;
    while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]])
            swap(a, b);

        res = merge(res, st.get(id[head[a]], id[a] + 1));
        a = p[head[a]];
    }

    if (depth[a] < depth[b])
        swap(a, b);

    res = merge(res, st.get(id[b], id[a] + 1));

    return res;
}

int main(void)
{
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);

    scanf("%d %d", &n, &q);
    st.init(n);
    v.resize(n + 5);
    head.resize(n + 5);
    id.resize(n + 5);
    depth.resize(n + 5);
    adj_list.resize(n + 5);
    sz.resize(n + 5);
    p.resize(n + 5);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1, 0);
    decompose(0, -1, 0);

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int i, v;
            scanf("%d %d", &i, &v);
            update_attraction(i - 1, v);
        }
        else {
            int i, j;
            scanf("%d %d", &i, &j);
            printf("%d\n", path(i - 1, j - 1));
        }
    }

    return 0;
}