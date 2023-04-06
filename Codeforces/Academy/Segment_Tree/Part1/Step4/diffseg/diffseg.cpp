#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, q;
int a[MAXN + 2];

struct segtree {

    int size = 1;
    vector<long long> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, 0);
    }

    void build(int* a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n) 
                tree[x] = (1ll<<a[lx]);
            else 
                tree[x] = 0;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] | tree[2 * x + 2];
    }
    void build(int* a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = (1ll<<v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) 
            set(i, v, 2 * x + 1, lx, mid);
        else 
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] | tree[2 * x + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    long long calc(int l, int r, int x, int lx ,int rx) {
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully containted
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = calc(l, r, 2 * x + 1, lx, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, rx);

        return s1 | s2;
    }
    long long calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int main(void) 
{
    scanf("%d %d", &n, &q);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    segtree st;
    st.init(n);
    st.build(a);

    while (q--) {
        int op;
        scanf("%d", &op);
        
        if (op == 2) {
            int i, v;
            scanf("%d %d", &i, &v);
            i--;
            st.set(i, v);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;
            auto res = st.calc(l ,r);

            int ans = 0;
            while (res) {
                if (res % 2)
                    ans++;
                res /= 2;
            }

            printf("%d\n", ans);
        }
    }

    return 0;
}