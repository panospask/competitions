#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;
    vector<bool> isnull;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        isnull.assign(2 * size, false);
    }

    void propagate(int x) {
        if (!isnull[x])
            return;

        isnull[2 * x + 1] = isnull[2 * x + 2] = true;
        tree[2 * x + 1] = tree[2 * x + 2] = 0;

        isnull[2 * x + 1] = false;
    }

    // Set the values from l to r to 0
    void nullify(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] = 0;
            isnull[x] = true;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        nullify(l, r, 2 * x + 1, lx, mid);
        nullify(l, r, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void nullify(int l, int r) {
        nullify(l, r, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    // Set the first 0 bit after i to 1
    bool set_after(int i, int x, int lx, int rx) {
        if (tree[x] == rx - lx) {
            // No 0 bits
            return false;
        }
        else if (lx == rx - 1) {
            tree[x] = 1;
            isnull[x] = false;

            return true;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        bool check = false;
        if (i < mid)
            check = set_after(i, 2 * x + 1, lx, mid);

        if (!check)
            check = set_after(i, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];

        return check;
    }
    void set_after(int i) {
        set_after(i, 0, 0, size);
    }

    int get(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        if (i < mid)
            return get(i, 2 * x + 1, lx, mid);
        else
            return get(i, 2 * x + 2, mid, rx);
    }
    int get(int i) {
        return get(i, 0, 0, size);
    }
};

struct Upd {
    int type;
    int node;
    int time;
};

int N, Q;
SegTree st;
vector<vector<int>> adj_list;
vector<int> par;
vector<int> dep;

vector<vector<int>> queries;
vector<Upd> updates;

void process(int node)
{
    ;
}

int main(void)
{
    ;
}