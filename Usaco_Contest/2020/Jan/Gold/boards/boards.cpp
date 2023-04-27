#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, INT_MIN);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = max(tree[x], v);
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int findmax(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r)
            return 0;
        else if (l <= lx && rx <= r)
            return tree[x];

        int mid = (lx + rx) / 2;
        return max(findmax(l, r, 2 * x + 1, lx, mid), findmax(l, r, 2 * x + 2, mid, rx));
    }
    int findmax(int l, int r) {
        return findmax(l, r, 0, 0, size);
    }
};

int n, p;
vector<int> ycords;
segtree TimeSaves;

struct point {
    bool isbegin;
    int ans_location;
    int x, y;

    void readpoint(bool b, int i) {
        isbegin = b;
        scanf("%d %d", &x, &y);
        if (y != 0)
            ycords.push_back(y);
        ans_location = i;
    }

    bool operator < (struct point& b) {
        return (this->x == b.x ? this->y < b.y : this->x < b.x);
    }
};
typedef struct point Point;
vector<Point> points;
vector<ll> time_taken;

int getY(int cord)
{
    return lower_bound(ycords.begin(), ycords.end(), cord) - ycords.begin();
}

int main(void)
{
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);

    scanf("%d %d", &n, &p);
    points.resize(2 * p);
    time_taken.resize(p);
    ycords.push_back(0);
    for (int i = 0; i < p; i++) {
        points[2 * i].readpoint(true, i);
        points[2 * i + 1].readpoint(false, i);
    }
    sort(ycords.begin(), ycords.end());
    sort(points.begin(), points.end());

    TimeSaves.init(ycords.size());
    TimeSaves.set(0, 0);
    for (auto Point : points) {
        if (Point.isbegin) {
            // We can use the springboard
            int save = TimeSaves.findmax(0, getY(Point.y) + 1);
            time_taken[Point.ans_location] = Point.x + (long long)Point.y - save;
        }
        else {
            // Check if we saved any time
            int timesave = Point.x + Point.y - time_taken[Point.ans_location];
            TimeSaves.set(getY(Point.y), timesave);
        }
    }

    int total_save = TimeSaves.findmax(0, ycords.size());
    printf("%d\n", 2 * n - total_save);
    return 0;
}