#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        return;
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    ll get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll res;
        if (i < mid)
            res = get(i, 2 * x + 1, lx, mid);
        else
            res = get(i, 2 * x + 2, mid, rx);

        return res + tree[x];
    }
    ll get(int i) {
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
            st.add(l, r, v);
        }
        else {
            int i;
            scanf("%d", &i);

            printf("%lld\n", st.get(i));
        }
    }

    return 0;
}