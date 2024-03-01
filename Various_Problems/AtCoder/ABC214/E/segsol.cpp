#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

struct Segtree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N)
            size *= 2;

        tree.assign(2 * size, 0);
    }

    void turn_on(int i, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = 1;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            turn_on(i, 2 * x + 1, lx, mid);
        else
            turn_on(i, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void turn_on(int i) {
        turn_on(i, 0, 0, size);
    }

    int calc(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;

        return calc(l, r, 2 * x + 1, lx, mid) + calc(l, r, 2 * x + 2, mid, rx);
    }
    int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

struct Point {
    int x;
    int id;
    bool end;
};

bool operator < (const Point& a, const Point& b)
{
    if (a.x == b.x)
        return a.end < b.end;
    return a.x < b.x;
}

Segtree st;
int N;
int rpos;
vector<Point> points;
vector<pi> balls;
vector<int> beg;

Point create(int x)
{
    return {x - 1, -1, 1};
}

int calculate(int pos)
{
    int lpos = lower_bound(points.begin(), points.end(), create(pos)) - points.begin();
    return pos + st.calc(lpos, rpos);
}

void solve(void)
{
    scanf("%d", &N);

    points.resize(2 * N);
    balls.resize(N);
    beg.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[2 * i].x, &points[2 * i + 1].x);
        points[2 * i].id = points[2 * i + 1].id = i;
        points[2 * i].end = false;
        points[2 * i + 1].end = true;

        balls[i].first = points[2 * i].x;
        balls[i].second = points[2 * i + 1].x;
    }
    sort(points.begin(), points.end());

    st.init(points.size());

    int optp = 0;
    for (int i = 0; i < 2 * N; i++) {
        Point cur = points[i];

        if (cur.end == false) {
            beg[cur.id] = i;
            continue;
        }

        rpos = lower_bound(points.begin(), points.end(), cur) - points.begin();

        st.turn_on(beg[cur.id]);
        if (calculate(optp) < calculate(balls[cur.id].first))
            optp = balls[cur.id].first;

        if (cur.x - calculate(optp) + 1 < 0) {
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