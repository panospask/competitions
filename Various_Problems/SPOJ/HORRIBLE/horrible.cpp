#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NO_OP = 0;
    const ll NEUTRAL = 0;

    void make_mod(ll& a, ll b, int len = 1) {
        a += (b * len);
    }

    int size;
    vector<ll> tree;
    vector<ll> op;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        op.assign(2 * size, NO_OP);
    }

    void propagate(int x, int lx, int rx) {

        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], op[x], mid - lx);
        make_mod(tree[2 * x + 2], op[x], rx - mid);
        make_mod(op[2 * x + 1], op[x]);
        make_mod(op[2 * x + 2], op[x]);

        op[x] = NO_OP;
    }

    void add(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v, rx - lx);
            make_mod(op[x], v);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        add(l, r, v, 2 * x + 1, lx, mid);
        add(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int l, int r, int v) {
        add(l, r, v, 0, 0, size);
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

        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, m;
SegTree st;

void solve(void)
{
    scanf("%d %d", &n, &m);

    st.init(n);
    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int l, r, v;
            scanf("%d %d %d", &l, &r, &v);
            l--;

            st.add(l, r, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%lld\n", st.calc(l, r));
        }
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}