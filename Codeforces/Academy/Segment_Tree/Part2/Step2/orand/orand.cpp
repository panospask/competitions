#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    const int NEUTRAL = -1;
    const int NO_OP = 0;

    int modify_operation(int a, int b) {
        return a | b;
    }
    int calc_operation(int a, int b) {
        return a & b;
    }

    void make_mod(int& a, int b) {
        a = modify_operation(a, b);
    }

    int size;
    vector<int> tree;
    vector<int> operations;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        operations.resize(2 * size);
        tree.resize(2 * size);
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

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = calc_operation(tree[2 * x + 1], tree[2 * x + 2]);
        make_mod(tree[x] ,operations[x]);
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

        int mid = (lx + rx) / 2;
        int res = calc_operation(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
        make_mod(res, operations[x]);

        return res;
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
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
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%d\n", st.calc(l, r));
        }
    }

    return 0;
}