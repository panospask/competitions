#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size = 1;
    vector<long long> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
    }

    void build(vector<int>&a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = 0;

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
        if (l <= lx && rx <= r) {
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

int n, m;
vector<int> a;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &m);
    a.resize(n);
    st.init(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    st.build(a);

    int op, a, b;
    while (m--) {
        scanf("%d %d %d", &op, &a, &b);
        if (op == 1) {
            a--;
            st.set(a, b);
        }
        else {
            a--;
            printf("%lld\n", st.sum(a, b));
        }
    }

    return 0;
}