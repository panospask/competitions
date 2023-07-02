#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    struct Segment {
        ll sum;
        ll pref;
        ll suff;
        ll opt;
    };

    const Segment NEUTRAL = {0, 0, 0, 0};
    const int NO_OP = INT_MAX;

    Segment merge(Segment& a, Segment& b) {
        Segment c;
        c.sum = a.sum + b.sum;
        c.pref = max(a.pref, a.sum + b.pref);
        c.suff = max(b.suff, b.sum + a.suff);
        c.opt = max(a.suff + b.pref, max(a.opt, b.opt));

        return c;
    }

    void make_mod(Segment& a, int m, int len) {
        if (m == NO_OP)
            return;

        a.sum = m * (ll)len;
        a.pref = max(a.sum, 0ll);
        a.suff = max(a.sum, 0ll);
        a.opt = max(a.sum, 0ll);
    }
    void make_mod(int& a, int b) {
        a = (b == NO_OP ? a : b);
    }

    int size;
    vector<Segment> tree;
    vector<int> operations;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        operations.assign(2 * size, NO_OP);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], operations[x], mid - lx);
        make_mod(tree[2 * x + 2], operations[x], rx - mid);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v, rx - lx);
            make_mod(operations[x], v);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    Segment calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;

        Segment s1 = calc(l, r, 2 * x + 1, lx, mid);
        Segment s2 = calc(l, r, 2 * x + 2, mid, rx);
        return merge(s1, s2);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size).opt;
    }
};

int n, m;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &m);

    st.init(n);
    while (m--) {
        int l, r, v;
        scanf("%d %d %d", &l, &r, &v);

        st.modify(l, r, v);

        printf("%lld\n", st.calc(0, n));
    }

    return 0;
}