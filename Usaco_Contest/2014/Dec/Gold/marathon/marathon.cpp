#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct SegTree {
    struct SubRoute {
        int total;

        pi l_first;
        pi l_sec;
        pi r_first;
        pi r_sec;

        int skip;
    };
    const SubRoute NEUTRAL = {-1};
    const pi BAD = {INT_MAX, INT_MAX};

    int dist(pi& a, pi& b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    SubRoute create(pi a) {
        SubRoute c;
        c.total = 0;
        c.l_first = c.r_first = a;
        c.l_sec = c.r_sec = BAD;
        c.skip = 0;

        return c;
    }

    SubRoute merge(SubRoute a, SubRoute b) {
        if (b.total == NEUTRAL.total)
            return a;
        if (a.total == NEUTRAL.total)
            return b;

        SubRoute c;
        c.total = a.total + b.total;
        c.total += dist(a.r_first, b.l_first);
        c.skip = max(a.skip, b.skip);
        if (a.r_sec != BAD) {
            c.skip = max(c.skip,
            dist(a.r_sec, a.r_first) + dist(b.l_first, a.r_first) - dist(a.r_sec, b.l_first));
        }
        if (b.l_sec != BAD) {
            c.skip = max(c.skip,
            dist(b.l_sec, b.l_first) + dist(b.l_first, a.r_first) - dist(a.r_first, b.l_sec));
        }



        c.l_first = a.l_first;
        if (a.l_sec == BAD)
            c.l_sec = b.l_first;
        else
            c.l_sec = a.l_sec;

        c.r_first = b.r_first;
        if (b.r_sec == BAD)
            c.r_sec = a.r_first;
        else
            c.r_sec = b.r_sec;

        return c;
    }

    int size;
    vector<SubRoute> tree;

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
        return;
    }

    void init(int n, vector<pi>& a) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
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
        return;
    }
    void set(int i, pi v) {
        set(i, v, 0, 0, size);
    }

    SubRoute calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return NEUTRAL;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return merge(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    int calc(int l, int r) {
        SubRoute ans = calc(l, r, 0, 0, size);
        return ans.total - ans.skip;
    }
};

int n, q;
vector<pi> a;
SegTree st;

int main(void)
{
    freopen("marathon.in", "r", stdin);
    freopen("marathon.out", "w", stdout);

    scanf("%d %d", &n, &q);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &a[i].first, &a[i].second);

    st.init(n, a);

    while (q--) {
        char op;
        scanf(" %c", &op);

        if (op == 'U') {
            int i, x, y;
            scanf("%d %d %d", &i, &x, &y);
            i--;

            st.set(i, mp(x, y));
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