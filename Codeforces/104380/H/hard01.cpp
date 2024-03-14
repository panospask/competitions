#include <bits/stdc++.h>

using namespace std;

struct SegTree {
    struct Segment {
        int ones;
        int zeroes;
    };
    const Segment NEUTRAL = {0, 0};

    Segment create(int i) {
        Segment c = NEUTRAL;
        if (i)
            c.ones++;
        else
            c.zeroes++;

        return c;
    }

    Segment merge(Segment& a, Segment& b) {
        Segment c;

        if (a.zeroes < b.ones) {
            c.ones = a.ones + b.ones - a.zeroes;
            c.zeroes = b.zeroes;
        }
        else {
            c.ones = a.ones;
            c.zeroes = b.zeroes + a.zeroes - b.ones;
        }

        return c;
    }

    int size;
    vector<Segment> tree;

    void build(vector<int>& a, int x, int lx, int rx) {
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
        return;
    }

    void init(int n, vector<int>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
        build(a, 0, 0, size);
    }

    void invert(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x].ones = !tree[x].ones;
            tree[x].zeroes = !tree[x].zeroes;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            invert(i, 2 * x + 1, lx, mid);
        else
            invert(i, 2 * x + 2, mid, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
        return;
    }
    void invert(int i) {
        invert(i, 0, 0, size);
    }

    Segment calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        auto s1 = calc(l, r, 2 * x + 1, lx, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, rx);

        return merge(s1, s2);
    }
    int calc(int l, int r) {
        auto ans = calc(l, r, 0, 0, size);
        return ans.ones + ans.zeroes;
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
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int i;
            scanf("%d", &i);
            i--;

            st.invert(i);
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%d\n", st.calc(l, r));
        }
    }

    return 0;
}