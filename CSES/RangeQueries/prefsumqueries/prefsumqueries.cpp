#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    struct Node {
        ll prefmax;
        ll total;
    };
    const Node NEUTRAL = {0, 0};

    Node create(int v) {
        return {max(v, 0), v};
    }

    Node merge(Node a, Node b) {
        Node c;
        c.total = a.total + b.total;
        c.prefmax = max(a.prefmax, a.total + b.prefmax);

        return c;
    }

    int size;
    vector<Node> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = create(a[lx]);
            else
                tree[x] = NEUTRAL;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = create(v);
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

    Node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        Node c1 = calc(l, r, 2 * x + 1, lx, mid);
        Node c2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(c1, c2);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size).prefmax;
    }
};

int n, m;
vector<int> a;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &m);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n, a);
    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int i, v;
            scanf("%d %d", &i, &v);
            i--;

            st.set(i, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%lld\n", st.calc(l, r));
        }
    }

    return 0;
}