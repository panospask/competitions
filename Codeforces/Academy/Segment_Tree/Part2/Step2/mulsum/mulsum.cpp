#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NEUTRAL = 0;
    const ll NO_OP = 1;
    const int MOD = (int)1e9 + 7;

    ll operation_mod(ll a, ll b) {
        return a * b % MOD;
    }
    ll operation_calc(ll a, ll b) {
        return (a + b) % MOD;
    }
    void apply_mod(ll &a, ll b) {
        a = operation_mod(a, b);
    }

    int size;
    vector<ll> tree;
    vector<ll> operations;

    void build(int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        build(v, 2 * x + 1, lx, mid);
        build(v, 2 * x + 2, mid, rx);

        tree[x] = operation_calc(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, int v) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operations.assign(2 * size, NO_OP);

        build(v, 0, 0, size);
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            apply_mod(tree[x], v);
            apply_mod(operations[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = operation_calc(tree[2 * x + 1], tree[2 * x + 2]);
        apply_mod(tree[x], operations[x]);
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
        ll res = operation_calc(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
        apply_mod(res, operations[x]);

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

    st.init(n, 1);
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