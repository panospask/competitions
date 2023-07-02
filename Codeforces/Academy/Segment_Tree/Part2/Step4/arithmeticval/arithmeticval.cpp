#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NO_OP = 0;
    const ll NEUTRAL = 0;

    int size;
    vector<ll> tree;
    vector<ll> operations;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.assign(2 * size, NO_OP);
        operations.assign(2 * size, NO_OP);
    }

    void modify(int l, int r, ll a, ll d, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += a;
            operations[x] += d;
            return;
        }

        int mid = (lx + rx) / 2;

        modify(l, r, a, d, 2 * x + 1, lx, mid);
        modify(l, r, a + d * (mid - lx), d, 2 * x + 2, mid, rx);

        return;
    }
    void modify(int l, int r, int a, int d) {
        modify(l, r, a + (ll)(0 - l) * d, d, 0, 0, size);
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

        res += tree[x];
        res += (i - lx) * operations[x];

        return res;
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
            int l, r, a, d;
            scanf("%d %d %d %d", &l, &r, &a, &d);

            st.modify(--l, r, a, d);
        }
        else {
            int i;
            scanf("%d", &i);

            printf("%lld\n", st.get(--i));
        }
    }

    return 0;
}