#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n;
int a[MAXN + 2];

struct segtree {

    int size = 1;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        
        tree.resize(2 * size);
    }

    void build(int* a, int ind, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            if (l_x < n)
                tree[ind] = a[l_x];
            else 
                tree[ind] = 0;

            return;
        }

        int mid = (l_x + r_x) / 2;
        build(a, 2 * ind + 1, l_x, mid);
        build(a, 2 * ind + 2, mid, r_x);

        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }
    void build(int* a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int ind, int lx, int rx) {
        if (lx == rx - 1) {
            tree[ind] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * ind + 1, lx, mid);
        else 
            set(i, v, 2 * ind + 2, mid, rx);

        tree[ind] = tree[2 * ind + 1] + tree[2 * ind + 2];
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int total(int l, int r, int ind, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        if (l <= lx && rx <= r) {
            // Fully contained
            return tree[ind];
        }

        int mid = (rx + lx) / 2;
        int s1 = total(l, r, 2 * ind + 1, lx, mid);
        int s2 = total(l, r, 2 * ind + 2, mid, rx);

        return s1 + s2;
    }
    int total(int l, int r) {
        return total(l, r, 0, 0, size);
    }
};

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--; // Make 0-based
    }

    // Create a segment tree initialized at all zeroes 
    // The ith spot is 1  if we have passed the ith number and 0 otherwise 
    int found[n];
    for (int i = 0; i < n; i++)
        found[i] = false;

    segtree st;
    st.init(n);
    st.build(found);

    for (int i = 0; i < n; i++) {
        int curv = a[i];

        // Check how many values greater that a[i] we have already visited
        int ans = st.total(curv + 1, n);

        printf("%d ", ans);

        // And set the current value to visited
        st.set(a[i], 1);
    }
    printf("\n");

    return 0;
}