#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<long long int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }
    long long sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

int n, q;
vector<int> original;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    original.resize(n);
    st.init(n + 2);
    for (int i = 0; i < n; i++)
        scanf("%d", &original[i]);

    int op;
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            int a, b, v;
            scanf("%d %d %d", &a, &b, &v);
            a--;
            st.add(a, v);
            st.add(b, -v);
        }
        else {
            int k;
            scanf("%d", &k);
            k--;
            printf("%lld\n", original[k] + st.sum(0, k+1));
        }
    }

    return 0;
}