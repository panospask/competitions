#include <bits/stdc++.h>

using namespace std;

struct SparseTree {
    struct Node {
        Node *l;
        Node* r;
        int val;
        int lazy = 0;

        Node(int v) : val(v), l(nullptr), r(nullptr) {};
        Node(Node* a, Node* b) : val(a->val + b->val), l(a), r(b) {};
    };

    int size;
    Node *null = new Node(0), *root;

    void init(int n) {
        size = n;
        null->l = null;
        null->r = null;
        null->val = 0;
        root = null;
    }

    void prop(Node* x, int lx, int rx) {
        if (x->lazy == 0)
            return;

        int mid = (lx + rx) / 2;
        if (x->l == null)
            x->l = new Node(null, null);
        if (x->r == null)
            x->r = new Node(null, null);

        x->l->lazy = x->r->lazy = x->lazy;
        x->l->val = (mid - lx) * x->l->lazy;
        x->r->val = (rx - mid) * x->r->lazy;

        x->lazy = 0;
    }

    Node* set(int l, int r, int v, Node* x, int lx, int rx)
    {
        if (x == null)
            x = new Node(null, null);

        if (l >= rx || lx >= r)
            return x;
        else if (l <= lx && rx <= r) {
            x->lazy = v;
            x->val = (rx - lx) * v;
            return x;
        }

        prop(x, lx, rx);

        int mid = (lx + rx) / 2;
        x->l = set(l, r, v, x->l, lx, mid);
        x->r = set(l, r, v, x->r, mid, rx);
        x->val = x->l->val + x->r->val;

        return x;
    }
    void set(int l, int r, int v) {
        root = set(l, r, v, root, 0, size);
    }

    int get(int l, int r, Node* x, int lx, int rx) {
        if (l >= rx || lx >= r || x == null)
            return 0;
        else if (l <= lx && rx <= r)
            return x->val;

        prop(x, lx, rx);

        int mid = (lx + rx) / 2;
        int s1 = get(l, r, x->l, lx, mid);
        int s2 = get(l, r, x->r, mid, rx);

        return s1 + s2;
    }
    int get(int l, int r) {
        return get(l, r, root, 0, size);
    }
};

int n = 1e9, q;
SparseTree Tree;
int c = 0;

int main(void)
{
    scanf("%d", &q);
    Tree.init(n);

    while (q--) {
        int d, x, y;
        scanf("%d %d %d", &d, &x, &y);
        x += c - 1;
        y += c;
        if (d == 1) {
            c = Tree.get(x, y);
            printf("%d\n", c);
        }
        else
            Tree.set(x, y, 1);
    }

    return 0;
}