#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    const int NO_OP = 0;
    const int NEUTRAL = INT_MIN;

    void make_mod(int& a, int b) {
        a += b;
    }
    int calc_op(int a, int b) {
        return max(a, b);
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

    void propagate(int x, int lx, int rx) {
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

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = calc_op(tree[2 * x + 1], tree[2 * x + 2]);
        return;
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    int find_after(int l, int v, int x, int lx, int rx) {
        if (rx <= l || tree[x] < v)
            return -1;
        else if (lx == rx - 1)
            return lx;

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;

        int res = find_after(l, v, 2 * x + 1, lx, mid);
        if (res == -1)
            res = find_after(l, v, 2 *x + 2, mid, rx);

        return res;
    }
    int find_after(int l, int v) {
        return find_after(l, v, 0, 0, size);
    }
};

SegTree st;
int n, m;

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
            int l, v;
            scanf("%d %d", &v, &l);

            printf("%d\n", st.find_after(l, v));
        }
    }

    return 0;
}