#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct SegTree {
    const ll NEUTRAL = 0;
    const pi NO_OP = mp(0, 0);

    void make_mod(ll& a, pi op, int len) {
        if (op.f == 0)
            return;

        if (op.f == 1) {
            a += (ll)len * op.s;
        }
        else {
            a = (ll)len * op.s;
        }
    }
    void make_mod(pi& a, pi b) {
        if (b.f == 0)
            return;

        if (b.f == 1) {
            a.s += b.s;
        }
        else {
            a.s = b.s;
        }

        a.f = max(a.f, b.f);
    }

    int size;
    vector<ll> tree;
    vector<pi> operations;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.resize(2 * size);
        operations.assign(2 * size, NO_OP);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], operations[x], mid - lx);
        make_mod(tree[2 * x + 2], operations[x], rx - mid);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, pi op, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], op, rx - lx);
            make_mod(operations[x], op);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, op, 2 * x + 1, lx, mid);
        modify(l, r, op, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int l, int r, int v) {
        modify(l, r, mp(1, v), 0, 0, size);
    }
    void set(int l, int r, int v) {
        modify(l, r, mp(2, v), 0, 0, size);
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

        ll s1 = calc(l, r, 2 * x + 1, lx, mid);
        ll s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
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

            st.set(l, r, v);
        }
        else if (op == 2) {
            int l, r, v;
            scanf("%d %d %d", &l, &r, &v);

            st.add(l, r, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%lld\n", st.calc(l, r));
        }
    }

    return 0;
}