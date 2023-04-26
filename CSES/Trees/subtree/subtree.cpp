#include <bits/stdc++.h>
#define pb push_back

using namespace std;

struct segtree {

    int size;
    vector<long long> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, 0);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
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
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = sum(l, r, 2 * x + 1, lx, mid);
        auto s2 = sum(l, r, 2 * x + 2, mid, rx);
        return s1 + s2;
    }
    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int n, q;
vector<vector<int>> adj_list;
vector<int> tin;
vector<int> val;
vector<int> subtree_val;
vector<int> tout;
int counter = 0;
segtree st;

void euler_tour(int node, int parent)
{
    tin[node] = counter++;
    for (auto neigh : adj_list[node])
        if (neigh != parent)
            euler_tour(neigh, node);

    tout[node] = counter;
}

int main(void)
{
    scanf("%d %d", &n, &q);
    adj_list.resize(n);
    val.resize(n);
    tin.resize(n);
    tout.resize(n);
    subtree_val.resize(n);
    st.init(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }
    euler_tour(0, -1);

    for (int i = 0; i < n; i++)
        subtree_val[tin[i]] = val[i];
    st.build(subtree_val);

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            s--;
            st.set(tin[s], x);
        }
        else {
            int s;
            scanf("%d", &s);
            s--;
            printf("%lld\n", st.sum(tin[s], tout[s]));
        }
    }

    return 0;
}