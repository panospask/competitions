#include <bits/stdc++.h>

using namespace std;

struct Segtree {
    int operation(int a, int b) {
        return max(a, b);
    }

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] = operation(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        return;
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    int get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int res;
        if (i < mid) {
            res = get(i, 2 * x + 1, lx, mid);
        }
        else {
            res = get(i, 2 * x + 2, mid, rx);
        }

        return operation(res, tree[x]);
    }
    int get(int i) {
        return get(i, 0, 0, size);
    }
};

int n, m;
Segtree st;

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
            int x;
            scanf("%d", &x);

            printf("%d\n", st.get(x));
        }
    }

    return 0;
}