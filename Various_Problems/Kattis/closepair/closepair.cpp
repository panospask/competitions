#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    T dist(const Point b) {
        return sqrt(pow(this->x - b.x, 2.00) + pow(this->y - b.y, 2.00));
    }
};

bool xsort(const Point& a, const Point& b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool operator < (const Point& a, const Point& b) {
        if (a.y == b.y)
            return a.x < b.x;

        return a.y < b.y;
}

int n;
set<Point> active;
vector<Point> points;
T d;
pair<Point, Point> ans;

void solve(int t)
{
    active.clear();
    n = t;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    sort(points.begin(), points.end(), xsort);
    d = INFINITY;

    for (int i = 0; i < n; i++) {
        Point p = points[i];
        stack<Point> rm;

        Point p1;
        p1.y = p.y - d;
        p1.x = -1e9;
        Point p2;
        p2.y = p.y + d;
        p2.x = 1e9;
        for (auto it = active.lower_bound(p1); it != active.upper_bound(p2); it++) {
            Point v = *it;
            auto res = p.dist(v);
            if (res < d) {
                d = res;
                ans = make_pair(v, p);
            }
            if (v.x + d < p.x)
                rm.push(v);
        }
        while (!rm.empty()) {
            active.erase(rm.top());
            rm.pop();
        }
        active.insert(p);
    }

    printf("%.2lf %.2lf %.2lf %.2lf\n", ans.first.x, ans.first.y, ans.second.x, ans.second.y);
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t != 0) {
        solve(t);
        scanf("%d", &t);
    }

    return 0;
}