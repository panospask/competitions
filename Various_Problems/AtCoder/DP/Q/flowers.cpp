#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    const ll NEUTRAL = 0;
    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
    }

    void set(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, ll v) {
        set(i, v, 0, 0, size);
    }

    ll calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll c1 = calc(l, r, 2 * x + 1, lx, mid);
        ll c2 = calc(l, r, 2 * x + 2, mid, rx);

        return max(c1, c2);
    }
    ll calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int N;
vector<int> h, a;

SegTree st;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    h.resize(N);
    st.init(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
        h[i]--;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < N; i++) {
        ll best = st.calc(0, h[i]) + a[i];
        st.set(h[i], best);
    }

    printf("%lld\n", st.calc(0, N));

    return 0;
}