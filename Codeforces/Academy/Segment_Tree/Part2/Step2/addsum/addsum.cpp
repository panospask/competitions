#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NEUTRAL = 0;
    const ll NO_OP = 0;

    ll mod_operation(ll a, ll b, int len) {
        return a + b * len;
    }
    ll calc_operation(ll a, ll b) {
        return a + b;
    }

    void make_mod(ll& a, ll b, int len) {
        a = mod_operation(a, b, len);
    }

    int size;
    vector<ll> operations;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        operations.assign(2 * size, NO_OP);
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

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = calc_operation(tree[2 * x + 1], tree[2 * x + 2]);
        make_mod(tree[x], operations[x], rx - lx);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll res = calc_operation(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
        make_mod(res, operations[x], min(rx, r) - max(lx, l));

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