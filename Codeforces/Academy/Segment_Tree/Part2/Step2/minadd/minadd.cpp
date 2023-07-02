#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {

    const ll NEUTRAL = LLONG_MAX;

    int size;
    vector<ll> tree;
    vector<ll> operations;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operations.resize(2 * size);
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            operations[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]) + operations[x];
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll g1 = get(l, r, 2 * x + 1, lx, mid);
        ll g2 = get(l, r, 2 * x + 2, mid, rx);

        return min(g1, g2) + operations[x];
    }
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
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
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%lld\n", st.get(l, r));
        }
    }

    return 0;
}