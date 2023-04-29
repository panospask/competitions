#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
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

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
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
        return max(get(l, r, 2 * x + 1, lx, mid), get(l, r, 2 * x + 2, mid, rx));
    }
    int get(int l, int r) {
        return get(l , r, 0, 0, size);
    }
};

int n, q;
segtree st;
vector<vector<int>> adj_list;
vector<int> head;
vector<int> id;
vector<int> depth;
vector<int> subtree_size;
vector<int> p;
vector<int> v;
int counter = 0;

void dfs(int node, int par)
{
    if (par == -1)
        depth[node] = 0;
    else
        depth[node] = depth[par] + 1;

    p[node] = par;
    subtree_size[node] = 1;
    for (auto kid : adj_list[node])
        if (kid != par) {
            dfs(kid, node);
            subtree_size[node] += subtree_size[kid];
        }
}

void decompose(int node, int par, int h)
{
    id[node] = counter++;
    head[node] = h;
    st.set(id[node], v[node]);
    int heav = 0, h_id = -1;
    for (auto kid : adj_list[node])
        if (kid != par && subtree_size[kid] > heav) {
            heav = subtree_size[kid];
            h_id = kid;
        }

    if (h_id != -1)
        decompose(h_id, node, h);

    for (auto kid : adj_list[node])
        if (kid != par && kid != h_id)
            decompose(kid, node, kid);
}

int find_in_path(int a, int b)
{
    int res = 0;
    while(head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]])
            swap(a, b);

        res = max(res, st.get(id[head[a]], id[a] + 1));
        a = p[head[a]];
    }

    if (depth[a] < depth[b])
        swap(a, b);

    res = max(res, st.get(id[b], id[a] + 1));
    return res;
}

void upd_node(int x, int v)
{
    st.set(id[x], v);
}

int main(void)
{
    scanf("%d %d", &n, &q);
    v.resize(n);
    adj_list.resize(n);
    id.resize(n);
    head.resize(n);
    depth.resize(n);
    subtree_size.resize(n);
    p.resize(n);
    st.init(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    dfs(0, -1);
    decompose(0, -1, 0);

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            s--;
            upd_node(s, x);
        }
        else {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            printf("%d ", find_in_path(a, b));
        }
    }
    printf("\n");

    return 0;
}