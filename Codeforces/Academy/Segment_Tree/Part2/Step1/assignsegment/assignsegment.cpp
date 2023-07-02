#include <bits/stdc++.h>

using namespace std;

struct SegTree {

    const int NO_OPERATION = -1;
    int operate(int a, int b) {
        return (b == NO_OPERATION ? a : b);
    }

    int size;
    vector<int> tree;

    void propagate(int x, int lx, int rx) {
        tree[2 * x + 1] = operate(tree[2 * x + 1], tree[x]);
        tree[2 * x + 2] = operate(tree[2 * x + 2], tree[x]);

        tree[x] = NO_OPERATION;
    }

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NO_OPERATION);
    }

    void set(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] = operate(tree[x], v);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        set(l, r, v, 2 * x + 1, lx, mid);
        set(l, r, v, 2 * x + 2, mid, rx);

        return;
    }
    void set(int l, int r, int v) {
        set(l, r, v, 0, 0, size);
    }

    int get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return max(tree[x], 0);
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        int res;
        if (i < mid)
            res = get(i, 2 * x + 1, lx, mid);
        else
            res = get(i, 2 * x + 2, mid, rx);

        return res;
    }
    int get(int i) {
        return get(i, 0, 0, size);
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
            st.set(l, r, v);
        }
        else {
            int i;
            scanf("%d", &i);

            printf("%d\n", st.get(i));
        }
    }

    return 0;
}