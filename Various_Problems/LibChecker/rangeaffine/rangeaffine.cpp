#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct SegTree {
    struct Operation {
        ll a;
        ll b;
    };
    const Operation NO_OP = {1, 0};
    const int NEUTRAL = 0;

    void make_mod(ll& a, Operation op, int len) {
        a = ((a * op.a) + op.b * len) % MOD;
    }
    void make_mod(Operation& a, Operation b) {
        a.a = a.a * b.a % MOD;
        a.b = (b.a * a.b + b.b) % MOD;
    }

    int size;
    vector<ll> tree;
    vector<Operation> op;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (a.size() > lx)
                tree[x] = a[lx];
            else
                tree[x] = NEUTRAL;
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = (tree[2 * x + 1] + tree[2 * x + 2]) % MOD;
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        op.assign(2 * size, NO_OP);

        build(a, 0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], op[x], mid - lx);
        make_mod(tree[2 * x + 2], op[x], rx - mid);
        make_mod(op[2 * x + 1], op[x]);
        make_mod(op[2 * x + 2], op[x]);

        op[x] = NO_OP;
    }

    void modify(int l, int r, Operation v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v, rx - lx);
            make_mod(op[x], v);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = (tree[2 * x + 1] + tree[2 * x + 2]) % MOD;
    }
    void modify(int l, int r, int b, int c) {
        modify(l, r, {b, c}, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);

        return (c1 + c2) % MOD;
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, m;
vector<int> a;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &m);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n, a);
    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int l, r, b, c;
            scanf("%d %d %d %d", &l, &r, &b, &c);

            st.modify(l, r, b, c);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%lld\n", st.calc(l, r));
        }
    }

    return 0;
}