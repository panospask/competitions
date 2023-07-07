#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pi;

struct SegTree {
    const pi NO_OP = {0, 0};
    const int NEUTRAL = 0;

    void make_mod(ll& a, pi op, ll len) {
        a += op.first * len + op.second * (len * (len - 1) / 2);
    }
    void make_mod(pi& a, pi b) {
        a.first += b.first;
        a.second += b.second;
    }

    int size;
    vector<pi> operations;
    vector<ll> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = NEUTRAL;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operations.assign(2 * size, NO_OP);

        build(a, 0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        if (operations[x] == NO_OP)
            return;

        int mid = (lx + rx) / 2;
        make_mod(tree[2 * x + 1], operations[x], mid - lx);
        make_mod(operations[2 * x + 1], operations[x]);

        pi v = operations[x];
        v.first += (mid - lx) * v.second;
        make_mod(tree[2 * x + 2], v, rx - mid);
        make_mod(operations[2 * x + 2], v);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, ll v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], make_pair(v, 1), rx - lx);
            // printf("Modded %d to %d with %lld, value is %lld\n", lx, rx, v, tree[x]);
            make_mod(operations[x], make_pair(v, 1));
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v + mid - lx, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void modify(int l, int r, int v) {
        modify(l, r, v - l, 0, 0, size);
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
        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, m;
SegTree st;
vector<int> a;

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

        if (op == 1) {
            int l, r;
            scanf("%d %d", &l, &r);

            st.modify(--l, r, 1);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%lld\n", st.calc(--l, r));
        }
    }

    return 0;
}