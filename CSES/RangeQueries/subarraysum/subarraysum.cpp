#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct segment {
    ll best;
    ll pref;
    ll suff;
    ll total;

    segment(void) {;};
    segment(int b, int p, int s, int t) {
        best = b;
        pref = b;
        suff = s;
        total = t;
    }
};
typedef struct segment Segment;

Segment IDENTITY = Segment(0, 0, 0, 0);

Segment merge(Segment& a, Segment& b)
{
    Segment c;
    c.best = max(a.suff + b.pref, max(a.best, b.best));
    c.pref = max(a.pref, a.total + b.pref);
    c.suff = max(b.suff, b.total + a.suff);
    c.total = a.total + b.total;

    return c;
}

Segment single(int a)
{
    int v = max(a, 0);
    return Segment(v, v, v, a);
}

struct segtree {

    int size;
    vector<Segment> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = single(a[lx]);
            else
                tree[x] = IDENTITY;
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = single(v);
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
        set(i, v, 0, 0, size);
    }
};

int n, m;
vector<int> vals;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &m);
    vals.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &vals[i]);

    st.init(n);
    st.build(vals);

    while (m--) {
        int k, x;
        scanf("%d %d", &k, &x);
        k--;
        st.set(k, x);

        printf("%lld\n", st.tree[0].best);
    }

    return 0;
}