#include <bits/stdc++.h>

using namespace std;

const int MAXH = 1e5;

const int INF = 1e7;
typedef long long ll;

struct SegTree {
    const int NO_OP = 0;
    const int NEUTRAL = 1e7;

    int size;
    vector<int> operation;
    vector<int> tree;

    void build(int n, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = lx < n ? 0 : INF;
            return;
        }

        int mid = (lx + rx) / 2;
        build(n, 2 * x + 1, lx, mid);
        build(n, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        operation.assign(2 * size, NO_OP);
        build(n, 0, 0, size);
    }

    void propagate(int x) {
        tree[2 * x + 1] += operation[x];
        tree[2 * x + 2] += operation[x];
        operation[2 * x + 1] += operation[x];
        operation[2 * x + 2] += operation[x];

        operation[x] = NO_OP;
    }

    void modify(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x] += v;
            operation[x] += v;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        modify(l, r, v, 2 * x + 1, lx, mid);
        modify(l, r, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }

    int get(int i, int x, int lx, int rx) {
        if (lx == rx - 1)
            return tree[x];

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

    int lower_bound(int v, int x, int lx, int rx) {
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

    // Increment the first num numbers after l
    void increment(int l, int num) {
        int r = l + num - 1;

        int v = get(r, 0, 0, size);

        int first = max(lower_bound(v, 0, 0, size), l);
        int last = lower_bound(v + 1, 0, 0, size);

        // The range [l... first) can be freely incremented
        modify(l, first, 1, 0, 0, size);

        int remaining = num - (first - l);
        modify(last - remaining, last, 1, 0, 0, size);
    }
};

int n;
vector<pair<int, int>> masts;
SegTree st;

int main(void)
{
    scanf("%d", &n);

    masts.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &masts[i].first, &masts[i].second);
    sort(masts.begin(), masts.end());

    st.init(MAXH);
    for (int i = 0; i < n; i++) {
        st.increment(MAXH - masts[i].first, masts[i].second);
    }

    ll ans = 0;
    for (int i = 1; i <= MAXH; i++) {
        int v = st.get(MAXH - i);
        ans += (ll)v * (v - 1) / 2;
    }

    printf("%lld\n", ans);
}