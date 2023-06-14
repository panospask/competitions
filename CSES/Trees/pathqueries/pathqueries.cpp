#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {

    int size;
    vector<ll> tree;

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

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll s1 = calc(l, r, 2 * x + 1, lx, mid);
        ll s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, q;
vector<int> tin;
vector<int> tout;
vector<int> v;
vector<vector<int>> adj_list;
SegTree subtrees;

int counter = 0;

void dfs(int node, int par)
{
    tin[node] = counter++;

    for (auto kid : adj_list[node])
        if (kid != par)
            dfs(kid, node);

    tout[node] = counter++;
}

int main(void)
{
    scanf("%d %d", &n, &q);

    v.resize(n);
    tin.resize(n);
    tout.resize(n);
    adj_list.resize(n);
    subtrees.init(2 * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1);

    for (int i = 0; i < n; i++) {
        subtrees.set(tin[i], v[i]);
        subtrees.set(tout[i], -v[i]);
    }

    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int s, x;
            scanf("%d %d", &s, &x);
            s--;

            subtrees.set(tin[s], x);
            subtrees.set(tout[s], -x);
        }
        else {
            int s;
            scanf("%d", &s);
            s--;

            printf("%lld\n", subtrees.calc(0, tin[s] + 1));
        }
    }

    return 0;
}