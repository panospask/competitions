#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    struct Node {
        ll NormalSum;
        ll WeightedSum;
    };

    const Node NEUTRAL = {0, 0};
    const int NO_OP = 0;

    void make_mod(Node& a, int b, int lx, ll len) {
        a.NormalSum += b * len;
        a.WeightedSum += b * len * (lx + 1);
        a.WeightedSum += b * (len * (len - 1) / 2);
    }
    void make_mod(int& a, int b) {
        a += b;
    }

    Node merge(Node a, Node b) {
        Node c;
        c.NormalSum = a.NormalSum + b.NormalSum;
        c.WeightedSum = a.WeightedSum + b.WeightedSum;

        return c;
    }

    int size;
    vector<Node> tree;
    vector<int> operations;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.assign(2 * size, NEUTRAL);
        operations.assign(2 * size, NO_OP);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) {
                make_mod(tree[x], a[lx], lx, 1);
            }

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size );
    }

    void propagate(int x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(tree[2 * x + 1], operations[x], lx, mid - lx);
        make_mod(tree[2 * x + 2], operations[x], mid, rx - mid);
        make_mod(operations[2 * x + 1], operations[x]);
        make_mod(operations[2 * x + 2], operations[x]);

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v, lx, rx - lx);
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
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        return merge(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    ll calc(int l, int r) {
        Node res = calc(l, r, 0, 0, size);
        return res.WeightedSum - (l) * res.NormalSum;
    }
};

SegTree st;
int n, m;
vector<int> a;

int main(void)
{
    scanf("%d %d", &n, &m);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n);
    st.build(a);

    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int l, r, d;
            scanf("%d %d %d", &l, &r, &d);

            st.modify(--l, r, d);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%lld\n", st.calc(--l, r));
        }
    }

    return 0;
}