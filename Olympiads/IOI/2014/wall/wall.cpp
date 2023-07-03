#include <bits/stdc++.h>
#include "wall.h"

using namespace std;

struct SegTree {
    struct Node {
        int above;
        int below;
    };

    const int NO_OP = -1;
    const Node NEUTRAL = {0, INT_MAX};

    void make_mod(Node& a, Node op) {
        if (op.below < a.above) {
            a.above = op.below;
            a.below = op.below;
        }
        if (op.above > a.below) {
            a.below = op.above;
            a.above = op.above;
        }
        else {
            a.above = max(op.above, a.above);
            a.below = min(op.below, a.below);
        }

    }

    int size;
    vector<Node> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
    }

    void propagate(int x) {
        make_mod(tree[2 * x + 1], tree[x]);
        make_mod(tree[2 * x + 2], tree[x]);

        tree[x] = NEUTRAL;
    }

    void modify(int l, int r, Node& v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            make_mod(tree[x], v);
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);
    }
    void add(int l, int r, int h) {
        Node v;
        v.above = h;
        v.below = INT_MAX;

        modify(l, r, v, 0, 0, size);
    }
    void remove(int l, int r, int h) {
        Node v;
        v.below = h;
        v.above = 0;

        modify(l, r, v, 0, 0, size);
    }

    void print_all(int n, int f[], int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx >= n)
                return;

            int v;
            v = tree[x].above;

            f[lx] = v;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        print_all(n, f, 2 * x + 1, lx, mid);
        print_all(n, f, 2 * x + 2, mid, rx);

        return;
    }
    void print_all(int n, int f[]) {
        print_all(n, f, 0, 0, size);
    }
};

SegTree st;

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[])
{
    st.init(n);

    for (int i = 0; i < k; i++) {
        if (op[i] == 1) {
            st.add(left[i], right[i] + 1, height[i]);
        }
        else {
            st.remove(left[i], right[i] + 1, height[i]);
        }

    }
    st.print_all(n, finalHeight);

    return;
}