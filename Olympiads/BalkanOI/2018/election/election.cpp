#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    struct Node {
        int pref;
        int suff;
        int total;
        int ans;
    };

    Node NEUTRAL = {0, 0, 0, 0};

    Node create(int v) {
        Node c;
        c.pref = c.suff = max(v, 0);
        c.total = v;
        c.ans = max(v, 0);

        return  c;
    }

    Node merge(Node a, Node b) {
        Node c;
        c.pref = max(a.pref, a.total + b.pref);
        c.suff = max(b.suff, b.total + a.suff);
        c.total = a.total + b.total;

        c.ans = max(max(a.ans + b.total, a.total + b.ans), a.pref + b.suff);
        return c;
    }

    int size;
    vector<Node> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = create(a[lx]);
            else
                tree[x] = NEUTRAL;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        build(a, 0, 0, size);
    }

    Node calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        Node c1 = calc(l, r, 2 * x + 1, lx, mid);
        Node c2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(c1, c2);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size).ans;
    }
};

int n, q;
SegTree st;
vector<int> a;

int main(void)
{
    scanf("%d", &n);

    a.resize(n);

    for (int i = 0; i < n; i++) {
        char c;
        scanf(" %c", &c);
        a[i] = (c == 'T' ? 1 : -1);
    }

    scanf("%d", &q);

    st.init(n, a);
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;

        printf("%d\n", st.calc(l, r));
    }

    return 0;
}