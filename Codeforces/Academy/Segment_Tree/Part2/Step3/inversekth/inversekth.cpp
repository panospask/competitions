#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    const int NO_OP = 0;
    const int NEUTRAL = 0;

    void make_mod(int& a, int b, int len) {
        if (b == NO_OP)
            return;

        a = (len - a);
    }

    int size;
    vector<int> tree;
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
        make_mod(operations[2 * x + 1], operations[x], 1);
        make_mod(operations[2 * x + 2], operations[x], 1);

        operations[x] = 0;
    }

    void modify(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], 1, rx - lx);
            make_mod(operations[x], 1, 1);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, 2 * x + 1, lx, mid);
        modify(l, r, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void modify(int l, int r) {
        modify(l, r, 0, 0, size);
    }

    int kth_one(int k, int x, int lx, int rx) {
        if (tree[x] <= k)
            return -1;
        else if (lx == rx - 1)
            return lx;

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        int res = kth_one(k, 2 * x + 1, lx, mid);
        if (res == -1)
            res = kth_one(k - tree[2 * x + 1], 2 * x + 2, mid, rx);

        return res;
    }
    int kth_one(int k) {
        return kth_one(k, 0, 0, size);
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
            int l, r;
            scanf("%d %d", &l, &r);

            st.modify(l, r);
        }
        else {
            int k;
            scanf("%d", &k);

            printf("%d\n", st.kth_one(k));
        }
    }

    return 0;
}