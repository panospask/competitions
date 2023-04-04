#include <bits/stdc++.h>

using namespace std;

struct segment {
    long long sum;
    long long pref;
    long long suff;
    long long optimal;

    segment(int o, int p, int s, int t) {
        sum = t;
        optimal = o;
        pref = p;
        suff = s;
    }
    segment(void) {;};
};
typedef struct segment Segment;

Segment NULL_ELEMENT = Segment(0, 0, 0, 0);

Segment merge(Segment a, Segment b) 
{
    Segment c;
    c.sum = a.sum + b.sum;
    c.optimal = max(a.suff + b.pref, max(a.optimal, b.optimal)); // New highest value segment
    c.pref = max(a.pref, a.sum + b.pref); // New optimal prefix
    c.suff = max(b.suff, b.sum + a.suff); // New optimal suffix

    return c;
}

Segment single_elem(int v) 
{
    if (v < 0) 
        return Segment(0, 0, 0, v);
    else 
        return Segment(v, v, v, v);
}

struct segtree {

    int size = 1;
    vector<Segment> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(size * 2);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) 
                tree[x] = single_elem(a[lx]);
            else 
                tree[x] = NULL_ELEMENT;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>&a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = single_elem(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else 
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        return set(i, v, 0, 0, size);
    }

    Segment calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return NULL_ELEMENT;
        }
        if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = calc(l, r, 2 * x + 1, lx, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, rx);
        return merge(s1, s2);
    }
    Segment calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, m;
vector<int> a;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &m);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    st.init(n);
    st.build(a);

    printf("%lld\n", st.calc(0, n).optimal);

    while (m--) {
        int i, v;
        scanf("%d %d", &i, &v);
        st.set(i, v);

        auto ans = st.calc(0, n);
        printf("%lld\n", ans.optimal);
    }

    return 0;
}