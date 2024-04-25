#include <bits/stdc++.h>
#define pb push_back

using namespace std;

struct SegTree {
    int size;
    vector<int> tree;
    const int DEFAULT = 0;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void increment(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x]++;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            increment(i, 2 * x + 1, lx, mid);
        }
        else {
            increment(i, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void increment(int i) {
        increment(i, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return DEFAULT;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int c1 = calc(l, r, 2 * x + 1, lx, mid);
        int c2 = calc(l, r, 2 * x + 2, mid, rx);

        return c1 + c2;
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
SegTree st;
vector<int> a;
vector<int> vals;

int compress(int l)
{
    return lower_bound(vals.begin(), vals.end(), l) - vals.begin();
}

void solve(void)
{
    scanf("%d", &N);

    a.resize(N);
    st.init(N);
    vals.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        vals.pb(a[i]);
    }

    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    long long int ans = 0;
    for (int i = 0; i < N; i++) {
        int cur = compress(a[i]);

        ans += st.calc(cur + 1, N);
        st.increment(cur);
    }
    printf("%lld\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}