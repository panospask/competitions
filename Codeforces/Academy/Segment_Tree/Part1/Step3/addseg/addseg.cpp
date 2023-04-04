#include <bits/stdc++.h>

using namespace std;

int n, m;

struct segtree {

    int size = 1;
    vector<long long int> sums;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        sums.assign(size * 2, 0LL);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            sums[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) 
            set(i, v, 2 * x + 1, lx, mid);
        else 
            set(i, v, 2 * x + 2, mid, rx);

        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    long long calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return sums[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = calc(l, r, 2 * x + 1, lx, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 + s2;
    }
    long long calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int main(void) {
    scanf("%d %d", &n, &m);

    segtree st;   

    st.init(n+1); 
    // SOS!!!!!!! We have n + 1 possible positions, [0..n]
    // WA on test 3 fixed by it

    while (m--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int l, r, v;
            scanf("%d %d %d", &l, &r, &v);
            st.set(l, v);
            st.set(r, -v);
        }
        else {
            int i;
            scanf("%d", &i);

            long long int ans = st.calc(0, i + 1); // Take the prefix sum of [0...i] = [0...i+1)
            printf("%lld\n", ans);
        }
    }

    return 0;
}