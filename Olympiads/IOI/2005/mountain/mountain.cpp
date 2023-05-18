#include <bits/stdc++.h>

using namespace std;

struct SparseTree {

    struct Node {
        int endnode;
        int maxele;
        int lazy;

        Node* l;
        Node* r;

        Node(int v) : endnode(v), maxele(v), lazy(v), l(nullptr), r(nullptr) {};
        Node(Node* a, Node* b) : endnode(a->endnode + b->endnode), maxele(0), lazy(INT_MIN), l(a), r(b) {};
    };

    int size;
    Node* root, *null;

    void init(int n) {
        size = n;
        null = new Node(0);
        null->l = null->r = null;
        null->endnode = null->maxele = null->lazy = 0;
        root = null;
    }

    void propagate(Node* x, int lx, int rx) {
        if (x->lazy == INT_MIN)
            return;

        if (x->l == null)
            x->l = new Node(null, null);
        if (x->r == null)
            x->r = new Node(null, null);

        int mid = (lx + rx) / 2;
        x->l->lazy = x->r->lazy = x->lazy;

        x->l->endnode = (mid - lx) * x->l->lazy;
        x->l->maxele = max(x->l->endnode, x->l->lazy);

        x->r->endnode = (rx - mid) * x->r->lazy;
        x->r->maxele = max(x->r->endnode, x->r->lazy);

        x->lazy = INT_MIN;
    }

    Node* set(int l, int r, int v, Node* x, int lx, int rx) {
        if (x == null)
            x = new Node(null, null);

        if (l >= rx || lx >= r)
            return x;
        else if (l <= lx && rx <= r) {
            x->lazy = v;
            x->endnode = (rx - lx) * v;
            x->maxele = max(x->endnode, v);
            return x;
        }

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        x->l = set(l, r, v, x->l, lx, mid);
        x->r = set(l, r, v, x->r, mid, rx);

        x->endnode = x->l->endnode + x->r->endnode;
        x->maxele = max(x->l->maxele, x->l->endnode + x->r->maxele);

        return x;
    }
    void set(int l, int r, int v) {
        root = set(l, r, v, root, 0, size);
    }

    int find_first_above(int v, Node* x, int lx, int rx) {
        if (x->maxele <= v)
            return -1;
        if (lx == rx - 1)
            return lx;

        propagate(x, lx, rx);

        int mid = (lx + rx) / 2;
        int ans = find_first_above(v, x->l, lx, mid);
        if (ans == -1)
            ans = find_first_above(v - x->l->endnode, x->r, mid, rx);

        return ans;
    }
    int find_first_above(int v) {
        return find_first_above(v, root, 0, size);
    }
};

int n, q;
SparseTree Tree;

int main(void)
{
    scanf("%d", &n);
    Tree.init(n + 1);

    while (true) {
        char op;
        scanf(" %c", &op);
        if (op == 'E')
            break;
        else if (op == 'I') {
            int a, b, d;
            scanf("%d %d %d", &a, &b, &d);
            b++;

            Tree.set(a, b, d);
        }
        else {
            int v;
            scanf("%d", &v);

            int ans = Tree.find_first_above(v);
            if (ans == -1)
                ans = n + 1;
            ans--;

            printf("%d\n", ans);
        }
    }

    return 0;
}