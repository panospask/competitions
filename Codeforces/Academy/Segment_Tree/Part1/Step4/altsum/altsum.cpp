#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, m;
int a[MAXN + 2];

struct segtree {

    int size = 1;
    vector<long long> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        
        tree.assign(size * 2, 0LL);
    }

    void build(int* a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            // We are at [i..i+1) = i
            if (lx < n) {
                tree[x] = a[lx];
            }
            else {
                tree[x] = 0;
            }

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(int* a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

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

    long long calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
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

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (i % 2)
            a[i] *= -1;
    }
    scanf("%d", &m);

    segtree st;
    st.init(n);
    st.build(a);

    while (m--) {
        int op;
        scanf("%d", &op);
        if (op == 0) {
            int i, v;
            scanf("%d %d", &i, &v);
            i--;
            if (i % 2)
                v *= -1;
                
            st.set(i, v);
        }
        else {
            int l, r;   
            scanf("%d %d", &l, &r);
            l--;             

            auto ans = st.calc(l, r);

            if (l % 2)
                ans *= -1;

            printf("%lld\n", ans);
        }
    }

    return 0;
}