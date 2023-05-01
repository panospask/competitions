#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    Point operator - (Point b)
    {
        return {this->x - b.x, this->y - b.y};
    }

    double dist(Point b)
    {
        return sqrt(pow(this->x - b.x, 2.0) + pow(this->y - b.y, 2.0));
    }
};

ll cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}
ll dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

ll DoubleArea(Point a, Point b, Point c)
{
    return abs(cross(b - a, c - a));
}

bool InTriangle(Point a, Point b, Point c, Point p)
{
    return DoubleArea(a, b, c) == DoubleArea(a, b, p) + DoubleArea(a, c, p) + DoubleArea(b, c, p);
}

ll orient(Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

int n, m;
vector<Point> polygon;

bool onDisk(Point a, Point b, Point p)
{
    return dot(a - p, b - p) <= 0;
}

bool onSegment(Point a, Point b, Point p)
{
    return onDisk(a, b, p) && orient(a, b, p) == 0;
}

bool above_eq(Point a, Point b)
{
    return a.y >= b.y;
}

// True if segment[a,b] crosses ray coming from p
bool CrossRay(Point a, Point b, Point p)
{
    return (above_eq(a, p) - above_eq(b, p)) * orient(p, b, a) > 0;
}

void solve(int t)
{
    n = t;
    polygon.resize(n);
    bool rev = false;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &polygon[i].x, &polygon[i].y);
        if (i >= 2)
            if (orient(polygon[i-2], polygon[i-1], polygon[i]) < 0)
                rev = true;
    }
    if (rev)
        reverse(polygon.begin(), polygon.end());

    scanf("%d", &m);
    while (m--) {
        Point cur;
        scanf("%lld %lld", &cur.x, &cur.y);

        int crossing = 0;
        bool isgood = false;
        for (int i = 0; i < polygon.size() && !isgood; i++) {
            Point p1 = polygon[i];
            Point p2 = polygon[(i + 1)%n];
            if (onSegment(p1, p2, cur))
                isgood = true;
            crossing += CrossRay(p1, p2, cur);
        }

        if (isgood) {
            printf("on\n");
        }
        else if (crossing % 2)
            printf("in\n");
        else
            printf("out\n");
    }
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