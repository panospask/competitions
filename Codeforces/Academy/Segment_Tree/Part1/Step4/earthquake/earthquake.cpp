#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, m;

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n) {
            size *= 2;
        }

        tree.assign(2 * size, INT_MAX);
    }

    void build (int* a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < n) {
                tree[x] = a[lx];
            }
            else 
                tree[x] = INT_MAX;
            
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x + 2], tree[2 * x + 1]);
    }
    void build(int *a) {
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

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int calc_and_remove(int l, int r, int p, int x, int lx, int rx) {
        if (tree[x] > p) {
            return 0;
        }
        if (lx >= r || l >= rx) {
            // Disjoint segments
            return 0;
        }
        if (lx == rx - 1) {
            tree[x] = INT_MAX;
            return 1;
        }

        int mid = (lx + rx) / 2;
        auto s1 = calc_and_remove(l, r, p, 2 * x + 1, lx, mid);
        auto s2 = calc_and_remove(l, r, p, 2 * x + 2, mid, rx);

        tree[x] = min(tree[2 * x +1], tree[2 * x + 2]);
        return s1 + s2;
    }
    int calc_and_remove(int l, int r, int p) {
        return calc_and_remove(l, r, p, 0, 0, size);
    }
};

int a[MAXN + 2];
int main(void)
{
    scanf("%d %d", &n, &m); 
    
    segtree st;
    st.init(n);

    while (m--) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) {
            int i, h;
            scanf("%d %d", &i, &h);
            st.set(i, h);
        }
        else {
            int l, r, p;
            scanf("%d %d %d", &l, &r, &p);
            int ans = st.calc_and_remove(l, r, p);

            printf("%d\n", ans);
        }
    }

    return 0;
}