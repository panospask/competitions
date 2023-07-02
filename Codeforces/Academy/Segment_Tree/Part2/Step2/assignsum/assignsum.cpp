#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NO_OP = -1;
    const ll NEUTRAL = 0;

    ll mod_op(ll a, ll b, int len) {
        return (b == NO_OP ? a : b * len);
    }
    ll calc_op(ll a, ll b) {
        return (a + b);
    }

    void make_mod(ll& a, ll b, int len) {
        a = mod_op(a, b, len);
    }

    int size;
    vector<ll> tree;
    vector<ll> operations;

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

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v, rx - lx);
            make_mod(operations[x], v, 1);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = calc_op(tree[2 * x + 1], tree[2 * x + 2]);
        make_mod(tree[x], operations[x], rx - lx);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        ll res = calc_op(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid,rx));

        return res;
    }
    ll calc(int l, int r) {
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

            printf("%lld\n", st.calc(l, r));
        }
    }

    return 0;
}