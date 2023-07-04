#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    struct Segment {
        bool counts;
        int total;
        int max;

        int lpref;
        bool lval;

        int rpref;
        bool rval;
    };
    const Segment NEUTRAL = {false, 0, 0, 0, 0, 0};

    Segment create(bool v) {
        Segment c;
        c.counts = true;
        c.max = c.total = 1;
        c.lpref = c.rpref = 1;
        c.lval = c.rval = v;

        return c;
    }

    Segment merge(Segment& a, Segment& b) {
        if (!b.counts)
            return a;

        Segment c;
        c.counts = true;
        c.total = a.total + b.total;

        c.lval = a.lval;
        c.lpref = a.lpref;

        c.rval = b.rval;
        c.rpref = b.rpref;

        c.max = max(a.max, b.max);
        if (a.rval == b.lval) {
            c.max = max(c.max, a.rpref + b.lpref);
            if (a.lpref == a.total)
                c.lpref += b.lpref;
            if (b.rpref == b.total)
                c.rpref += a.rpref;
        }

        return c;
    }

    int size;
    vector<Segment> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size()) {
                tree[x] = create(a[lx]);
            }

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        build(a, 0, 0, size);
    }

    void invert(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = create(!tree[x].lval);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            invert(i, 2 * x + 1, lx, mid);
        else
            invert(i, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void invert(int i) {
        invert(i, 0, 0, size);
    }

    int longest(void) {
        return tree[0].max;
    }
};

int n, m;
vector<int> a;
SegTree st;

int main(void)
{
    char c;
    while (!isspace(c = getchar())) {
        a.push_back(c - '0');
        n++;
    }
    scanf("%d", &m);

    st.init(n, a);

    while (m--) {
        int i;
        scanf("%d", &i);
        i--;
        st.invert(i);

        printf("%d ", st.longest());
    }
    printf("\n");

    return 0;
}