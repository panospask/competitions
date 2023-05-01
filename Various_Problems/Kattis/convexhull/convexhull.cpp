#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    double dist(Point& x) {
        return sqrt(pow(this->x - x.x, 2.0) + pow(this->y - x.y, 2.0));
    }
};
Point operator - (const Point& a, const Point& b)
{
    return {a.x - b.x, a.y - b.y};
}
bool operator == (const Point& a, const Point& b)
{
    return a.x == b.x && a.y == b.y;
}

ll cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

ll orient(Point a, Point b, Point c)
{
    return cross(a - b, a - c);
}

int n;
Point chosen = {LONG_LONG_MAX, LONG_LONG_MAX};
vector<Point> points;
vector<Point> Hull;

bool sort_by_angle(Point& a, Point& b)
{
    if (a == chosen)
        return false;
    if (b == chosen)
        return true;
    ll res = cross(chosen - a, chosen - b);
    if (res == 0)
        return chosen.dist(a) < chosen.dist(b);

    return res > 0;
}


void solve(int t)
{
    n = t;
    Hull.clear();
    points.resize(n);
    chosen = {LONG_LONG_MAX, LONG_LONG_MAX};
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
        if (points[i].y < chosen.y)
            chosen = points[i];
        else if (points[i].y == chosen.y && points[i].x > chosen.x)
            chosen = points[i];
    }

    sort(points.begin(), points.end(), sort_by_angle);
    Hull.push_back(chosen);
    for (int i = 0; i < n - 1; i++) {
        Point cur = points[i];
        if (cur == chosen)
            break;
        while (Hull.size() >= 2) {
            if (orient(Hull[Hull.size() - 2], Hull.back(), cur) <= 0)
                Hull.pop_back();
            else
                break;
        }

        Hull.push_back(cur);
    }

    printf("%d\n", (int)Hull.size());
    for (auto p : Hull)
        printf("%lld %lld\n", p.x, p.y);

}
int main(void)
{
    scanf("%d", &n);
    while (n != 0) {
        solve(n);
        scanf("%d", &n);
    }

    return 0;
}