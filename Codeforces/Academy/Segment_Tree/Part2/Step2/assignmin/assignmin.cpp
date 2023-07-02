#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const int NEUTRAL = INT_MAX;
    const int NO_OP = -1;

    int mod_op(int a, int b) {
        return (b == NO_OP ? a : b);
    }
    int calc_op(int a, int b) {
        return min(a, b);
    }

    void make_mod(int& a, int b) {
        a = mod_op(a, b);
    }

    int size;
    vector<int> tree;
    vector<int> operations;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operations.assign(2 * size, NO_OP);
    }

    void propagate(int x) {
        make_mod(tree[2 * x + 1], operations[x]);
        make_mod(tree[2 * x + 2], operations[x]);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v);
            make_mod(operations[x], v);
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = calc_op(tree[2 * x + 1], tree[2 * x + 2]);
        make_mod(tree[x], operations[x]);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        int res = calc_op(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
        return res;
    }
    int calc(int l, int r ) {
        return calc(l, r, 0, 0, size);
    }
};

int n, m;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &m);

    st.init(n);
    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int l, r, v;
            scanf("%d %d %d", &l, &r, &v);

            st.modify(l, r, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%d\n", st.calc(l, r));
        }
    }

    return 0;
}