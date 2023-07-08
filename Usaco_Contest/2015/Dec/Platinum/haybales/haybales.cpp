#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct SegTree {
    struct Node {
        ll total;
        ll min;
    };
    const Node NEUTRAL = {0, (ll)1e13};
    const ll NO_OP = 0;

    void make_mod(Node& a, ll op, int len) {
        a.total += op * len;
        a.min += op;
    }
    void make_mod(ll& a, ll b) {
        a += b;
    }

    Node merge(Node a, Node b) {
        Node c;
        c.total = a.total + b.total;
        c.min = min(a.min, b.min);

        return c;
    }

    int size;
    vector<ll> operations;
    vector<Node> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = {a[lx], a[lx]};
            else
                tree[x] = NEUTRAL;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<int> a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operations.assign(2 * size, NO_OP);

        build(a, 0, 0, size);
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], operations[x], mid - lx);
        make_mod(tree[2 * x + 2], operations[x], rx - mid);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v, rx - lx);
            make_mod(operations[x], v);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, 0, 0, size);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;

        Node n1 = calc(l, r, 2 * x + 1, lx, mid);
        Node n2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(n1, n2);
    }
    ll total(int l, int r) {
        return calc(l, r, 0, 0, size).total;
    }
    ll minimum(int l, int r) {
        return calc(l, r, 0, 0, size).min;
    }
};

int n, q;
vector<int> a;
SegTree st;

int main(void)
{
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);

    scanf("%d %d", &n, &q);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n, a);
    while (q--) {
        char op;
        scanf(" %c", &op);

        if (op == 'P') {
            int l, r, v;
            scanf("%d %d %d", &l, &r, &v);
            l--;

            st.modify(l, r, v);
        }
        else if (op == 'M') {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%lld\n", st.minimum(l, r));
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%lld\n", st.total(l, r));
        }
    }

    return 0;
}