#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NO_OP = 0;
    const ll NEUTRAL = LLONG_MAX;

    int size;
    int n;
    vector<ll> tree;
    vector<ll> operations;

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

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<int>& a) {
        size = 1;
        this->n = n;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operations.assign(2 * size, NO_OP);

        build(a, 0, 0, size);
    }

    void propagate(int x) {
        tree[2 * x + 1] += operations[x];
        tree[2 * x + 2] += operations[x];
        operations[2 * x + 1] += operations[x];
        operations[2 * x + 2] += operations[x];

        operations[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            operations[x] += v;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + + 1], tree[2 * x + 2]);
    }

    ll get(int i, int x, int lx, int rx) {
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

    // Returns the first element more than or equal to v
    int lower_bound(ll v, int x, int lx, int rx) {
        if (tree[x] < v)
            return -1;
        else if (lx == rx - 1)
            return lx;

        propagate(x);

        int mid = (lx + rx) / 2;
        int res = lower_bound(v, 2 * x + 1, lx, mid);
        if (res == -1)
            res = lower_bound(v, 2 * x + 2, mid, rx);

        return res;
    }

    // Count elements with value in [minv, maxv]
    int count_between(int minv, int maxv) {
        int r = lower_bound(maxv + 1, 0, 0, size);
        int l = lower_bound(minv, 0, 0, size);

        return r - l;
    }

    // Increment the shortest num elements with height over minv
    void increment(int minv, int num) {
        // First element to be incremented
        int l = lower_bound(minv, 0, 0, size);
        if (l >= n)
            return;

        // Last element to be incremented
        int r = l + num - 1;
        if (r >= n) {
            modify(l, n, 1, 0, 0, size);
            return;
        }
        ll v = get(r, 0, 0, size);

        // First element equal to a[r]
        int first = lower_bound(v, 0, 0, size);
        // First element equal to (a[r] + 1)
        int last = lower_bound(v + 1, 0, 0, size);

        // The range [l.. f) can be freely incremented
        modify(l, first, 1, 0, 0, size);

        int left_to_inc = num - (first - l);
        // Increment the last elements equal to r
        modify(last - left_to_inc, last, 1, 0, 0, size);

        return;
    }
};

int n, m;
vector<int> a;
SegTree st;

int main(void)
{
    scanf("%d %d", &n, &m);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());

    st.init(n, a);
    while (m--) {
        char op;
        scanf(" %c", &op);

        if (op == 'F') {
            int c, h;
            scanf("%d %d", &c, &h);

            st.increment(h, c);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);

            printf("%d\n", st.count_between(l, r));
        }
    }

    return 0;
}