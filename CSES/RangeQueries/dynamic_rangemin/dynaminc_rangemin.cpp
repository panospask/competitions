#include <bits/stdc++.h>

using namespace std;

struct SegTree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (a.size() > lx)
                tree[x] = a[lx];
            else
                tree[x] = INT_MAX;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
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

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return INT_MAX;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;

        int a1 = calc(l, r, 2 * x + 1, lx, mid);
        int a2 = calc(l, r, 2 * x + 2, mid, rx);

        return min(a1, a2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, q;
vector<int> a;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);
    st.init(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.build(a);

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int k, u;
            scanf("%d %d", &k, &u);
            k--;

            st.set(k, u);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%d\n", st.calc(l, r));
        }
    }

    return 0;
}