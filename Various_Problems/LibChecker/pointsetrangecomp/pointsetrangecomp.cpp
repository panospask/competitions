#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

struct LinearFunction {
    ll a, b;
};
const LinearFunction NEUTRAL = {1, 0};

struct SegTree {
    // h(x) = g(f(x))
    LinearFunction merge(LinearFunction& f, LinearFunction& g) {
        LinearFunction h;
        h.a = g.a * f.a % MOD;
        h.b = (g.a * f.b % MOD + g.b) % MOD;

        return h;
    }

    int size;
    vector<LinearFunction> tree;

    void build(vector<LinearFunction>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n,vector<LinearFunction>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        build(a, 0, 0, size);
    }

    void set(int i, LinearFunction v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, LinearFunction v) {
        set(i, v, 0, 0, size);
    }

    LinearFunction calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        LinearFunction l1 = calc(l, r, 2 * x + 1, lx, mid);
        LinearFunction l2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(l1, l2);
    }
    LinearFunction calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, q;
vector<LinearFunction> a;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &a[i].a, &a[i].b);
    }

    st.init(n, a);
    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 0) {
            int i;
            LinearFunction l;
            scanf("%d %lld %lld", &i, &l.a, &l.b);

            st.set(i, l);
        }
        else {
            int l, r, x;
            scanf("%d %d %d", &l, &r, &x);

            LinearFunction ans = st.calc(l, r);
            ll res = (ans.a * x + ans.b) % MOD;

            printf("%lld\n", res);
        }
    }

    return 0;
}