#include <bits/stdc++.h>

using namespace std;

// Sparse segment tree implementation

typedef long long ll;

struct SegTree {
    const int NO_OP = 0;

    struct Node {
        ll total;
        ll change;
        ll max;
        Node *l, *r;

        Node(int a, int b, Node* c, Node* d) : total(a), change(b), max(0), l(c), r(d) {};
    };

    Node* null = new Node(0, 0, nullptr, nullptr);

    int size;
    Node* root;

    void make_mod(Node*& a, ll op, int len) {
        if (a == null) {
            a = new Node(0, 0, null, null);
        }

        if (op == NO_OP)
            return;

        a->change += op;
        a->total += op * len;
        // a->max += op * len;
        a->max = max(a->max, 0ll);
    }

    void init(int n) {
        null->l = null->r = null;
        size = 1;
        while (size < n)
            size *= 2;

        root = null;
    }

    void propagate(Node* x, int lx, int rx) {
        int mid = (lx + rx) / 2;

        make_mod(x->l, x->change, mid - lx);
        make_mod(x->r, x->change, rx - mid);

        x->change = NO_OP;
    }

    void modify(int l, int r, int v, Node* x, int lx, int rx) {
        if (x == null)
            x = new Node(0, 0, null, null);

        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(x, v, rx - lx);
            return;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        modify(l, r, v, x->l, lx, mid);
        modify(l, r, v, x->r, mid, rx);

        x->total = x->l->total + x->r->total;
        x->max = max(x->l->max, x->l->total + x->r->max);
    }
    void modify(int l, int r, int v) {
        modify(l, r, v, root, 0, size);
    }

    int find_pos(ll h, Node* x, int lx, int rx) {
        if (x->max <= h)
            return -1;
        if (x == null)
            x = new Node(0, 0, null, null);

        if (lx == rx - 1)
            return lx;

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        int res = find_pos(h, x->l, lx, mid);
        if (res == -1)
            res = find_pos(h + x->l->total, x->r, mid, rx);

        return res;
    }
    int find_pos(ll h) {
        return find_pos(h, root, 0, size);
    }
};

int n;
SegTree st;

int main(void)
{
    scanf("%d", &n);

    st.init(n);

    char c;
    scanf(" %c", &c);

    while (c != 'E') {
        if (c == 'I') {
            int a, b, d;
            scanf("%d %d %d", &a, &b, &d);
            a--;

            st.modify(a, b, d);
        }
        else {
            int h;
            scanf("%d", &h);

            int res = st.find_pos(h);
            if (res == -1 || res >= n)
                res = n;

            printf("%d\n", res);
        }

        scanf(" %c", &c);
    }

    return 0;
}