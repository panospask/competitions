#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
    int size;
    vector<ll> tree;
    
    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = tree[2 * x + 1]  + tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, mid);
        ll s2 = sum(l, r, 2 * x + 2, mid, rx);
        return s1 + s2;
    }
    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int N, Q;
SegTree st;

int main(void) {
    scanf("%d %d", &N, &Q);
    
    st.init(N);
    for (int i = 0; i < N; i++) {
        int v;
        scanf("%d", &v);
        st.set(i, v);
    }

    while (Q--) {
        int t, a, b;
        scanf("%d %d %d", &t, &a, &b);
        if (t == 1) {
            st.set(a - 1, b);
        }
        else {
            printf("%lld\n", st.sum(a - 1, b));
        }
    }

    return 0;
}