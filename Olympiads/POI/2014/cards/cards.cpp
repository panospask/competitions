#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

struct SegTree {
    const int BAD = -1;

    struct Segment {
        // Values that the first card in the segment can take
        int fmin, fmax;

        // Values that the last card in the segment MUST take if the first takes the corresponding
        // If it is impossible to create a segment with a choice of f_val, then BAD
        int lmin, lmax;
    };
    const Segment NEUTRAL = {-1, -1, -1, -1};

    Segment create(pi& a) {
        if (a.f > a.s)
            swap(a.f, a.s);
        return {a.f, a.s, a.f, a.s};
    }

    Segment merge(Segment& a, Segment& b) {
        if (b.fmax == NEUTRAL.fmax && b.fmin == NEUTRAL.fmin)
            return a;

        Segment c;
        // What if a takes the small value
        c.fmin = a.fmin;
        if (a.lmin == BAD) {
            c.lmin = BAD;
        }
        else {
            if (b.fmin >= a.lmin)
                c.lmin = b.lmin;
            else if (b.fmax >= a.lmin)
                c.lmin = b.lmax;
            else
                c.lmin = BAD;
        }

        // What if a takes the large value
        c.fmax = a.fmax;
        if (a.lmax == BAD) {
            c.lmax = BAD;
        }
        else {
            if (b.fmin >= a.lmax)
                c.lmax = b.lmin;
            else if (b.fmax >= a.lmax)
                c.lmax = b.lmax;
            else
                c.lmax = BAD;
        }

        return c;
    }

    int size;
    vector<Segment> tree;

    void build(vector<pi>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = create(a[lx]);
            else
                tree[x] = NEUTRAL;

            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int n, vector<pi>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, NEUTRAL);
        build(a, 0, 0, size);
    }

    void set(int i, pi v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = create(v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, pi v) {
        set(i, v, 0, 0, size);
    }

    bool able(void) {
        return tree[0].lmax != BAD  || tree[0].lmin != BAD;
    }
};

int n, m;
vector<pi> a;
SegTree st;

int main(void)
{
    scanf("%d", &n);
    a.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i].f, &a[i].s);
    }
    scanf("%d", &m);

    st.init(n, a);
    while (m--) {
        int i, j;
        scanf("%d %d", &i, &j);
        i--; j--;

        st.set(i, a[j]);
        st.set(j, a[i]);
        swap(a[j], a[i]);

        if (st.able())
            printf("TAK\n");
        else
            printf("NIE\n");
    }

    return 0;
}