#include "game.h"
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

long long gcd2(long long X, long long Y) {
    long long tmp;
    while (X != Y && Y != 0) {
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

struct SegTree {
    const ll NEUTRAL = 0;

    struct Node {
        ll v;
        Node* l, * r;
        int skip_pos;

        Node(ll a, Node* b, Node* c) : v(a), l(b), r(c) {skip_pos = -1;}
    };

    int size;
    Node* root, *null;
    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        null = new Node(0, nullptr, nullptr);
        null->l = null->r = null;
        root = null;
    }

    Node* set(int i, ll v, Node* x, int lx, int rx) {
        if (x == null)
            x = new Node(0, null, null);

        if (lx == rx - 1) {
            x->v = v;
            return x;
        }

        int mid = (lx + rx) / 2;
        if (x->skip_pos == -1 || x->skip_pos == i) {
            x->skip_pos = i;
            x->v = v;

            return x;
        }
        else if (x->skip_pos != -2) {
            if (x->skip_pos < mid) {
                x->l = set(x->skip_pos, x->v, x->l, lx, mid);
            }
            else {
                x->r = set(x->skip_pos, x->v, x->r, mid, rx);
            }

            x->skip_pos = -2;
        }

        if (i < mid) {
            x->l = set(i, v, x->l, lx, mid);
        }
        else {
            x->r = set(i, v, x->r, mid, rx);
        }
        x->v = gcd2(x->l->v, x->r->v);

        return x;
    }
    void set(int i, ll v) {
        root = set(i, v, root, 0, size);
    }

    ll calc(int l, int r, Node* x, int lx, int rx) {
        if (l >= rx || lx >= r || x == null) {
            return NEUTRAL;
        }
        if (x->skip_pos >= 0) {
            int p = x->skip_pos;
            if (p >= l && p < r)
                return x->v;
            else
                return NEUTRAL;
        }
        if (l <= lx && rx <= r) {
            ll ret = x->v;
            return ret;
        }

        int mid = (lx + rx) / 2;
        ll c1 = calc(l, r, x->l, lx, mid);
        ll c2 = calc(l, r, x->r, mid, rx);

        return gcd2(c1, c2);
    }
    ll calc(int l, int r) {
        return calc(l, r, root, 0, size);
    }
};

struct Tree2D {
    const ll NEUTRAL = 0;

    struct Node {
        SegTree col;
        Node *l, * r;

        Node(int sz, Node* a, Node* b) : l(a), r(b) {col.init(sz);}
    };

    Node *root, *null;

    int row_size;
    int col_size;
    void init(int n, int m) {
        row_size = 1;
        while (row_size < n)
            row_size *= 2;
        col_size = m;

        null = new Node(col_size, nullptr, nullptr);
        null->l = null->r = null;
        root = null;
    }

    ll calc(int i_l, int i_r, int j_l, int j_r, Node* x, int lx, int rx) {
        if (i_l >= rx || lx >= i_r || x == null)
            return NEUTRAL;

        if (i_l <= lx && rx <= i_r) {
            return x->col.calc(j_l, j_r);
        }

        int mid = (lx + rx) / 2;
        ll c1 = calc(i_l, i_r, j_l, j_r, x->l, lx, mid);
        ll c2 = calc(i_l, i_r, j_l, j_r, x->r, mid, rx);

        return gcd2(c1, c2);
    }
    ll calc(int i_l, int i_r, int j_l, int j_r) {
        return calc(i_l, i_r, j_l, j_r, root, 0, row_size);
    }

    Node* set(int i, int j, ll v, Node* x, int lx, int rx) {
        if (x == null)
            x = new Node(col_size, null, null);

        if (lx == rx - 1) {
            x->col.set(j, v);
            return x;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            x->l = set(i, j, v, x->l, lx, mid);
        }
        else {
            x->r = set(i, j, v, x->r, mid, rx);
        }

        ll new_v = gcd2(x->l->col.calc(j, j + 1), x->r->col.calc(j, j + 1));
        x->col.set(j, new_v);

        return x;
    }
    void set(int i, int j, ll v) {
        root = set(i, j, v, root, 0, row_size);
    }
};

Tree2D board;

void init(int R, int C) {
    board.init(R, C);
}

void update(int P, int Q, long long K) {
    board.set(P, Q, K);
}

long long calculate(int P, int Q, int U, int V) {
    return board.calc(P, U + 1, Q, V + 1);
}
