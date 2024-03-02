#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

struct Segtree {
    int size;
    vector<int> tree;
    vector<int> op;

    void init(int N) {
        size = 1;
        while (size < N)
            size *= 2;

        tree.assign(2 * size, 0);
        op.assign(2 * size, 0);
    }

    void propagate(int x) {
        if (op[x]) {
            tree[2 * x + 1] += op[x];
            tree[2 * x + 2] += op[x];
            op[2 * x + 1] += op[x];
            op[2 * x + 2] += op[x];
        }

        op[x] = 0;
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = tree[x] + v;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    void increment(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x]++;
            op[x]++;
            return;
        }

        propagate(x);
        int mid = (lx + rx) / 2;

        increment(l, r, 2 * x + 1, lx, mid);
        increment(l, r, 2 * x + 2, mid, rx);
        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void increment(int l, int r) {
        increment(l, r, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        propagate(x);

        int mid = (lx + rx) / 2;

        return max(calc(l, r, 2 * x + 1, lx, mid), calc(l, r, 2 * x + 2, mid, rx));
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct Point {
    int start, end;
    int id;
};

bool operator < (const Point& a, const Point& b)
{
    if (a.end == b.end)
        return a.start > b.start;
    return a.end < b.end;
}

Segtree st;
int N;
vector<Point> points;
set<int> bestlefts;
vector<int> startpoints;

void solve(void)
{
    scanf("%d", &N);

    bestlefts.clear();
    points.resize(N);
    startpoints.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].start, &points[i].end);
        points[i].id = i;
        startpoints[i] = points[i].start;
    }
    sort(points.begin(), points.end());

    sort(startpoints.begin(), startpoints.end());
    startpoints.resize(unique(startpoints.begin(), startpoints.end()) - startpoints.begin());

    st.init(startpoints.size());
    for (int i = 0; i < startpoints.size(); i++) {
        st.add(i, startpoints[i]);
    }

    int best = 0;
    for (int i = 0; i < N; i++) {
        Point cur = points[i];

        int rpos = upper_bound(startpoints.begin(), startpoints.end(), cur.end) - startpoints.begin();
        int lpos = lower_bound(startpoints.begin(), startpoints.end(), cur.start) - startpoints.begin();

        st.increment(0, lpos + 1);

        if (st.calc(0, rpos) > cur.end + 1) {
            printf("No\n");
            return;
        }
    }

    printf("Yes\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}