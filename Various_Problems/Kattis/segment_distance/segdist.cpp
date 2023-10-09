#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    Point(void) {;}
    Point(T a, T b) {x = a; y = b;}

    Point operator + (Point b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator * (T b) {
        return Point (x * b, y * b);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    void read(void) {
        int a, b;
        scanf("%d %d", &a, &b);
        x = a;
        y = b;
    }
};

T len(Point p) {
    return sqrt(p.x * p.x + p.y * p.y);
}

T dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}
T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

// Positive if ABC is left turn
// Negative if ABC is right turn
// 0 if ABC is straight line
T orient(Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

struct Line {
    Point v;
    T c;

    Line(Point p, Point q) {
        v = q - p;
        c = cross(v, p);
    }

    bool before(Point p, Point q) {
        return dot(v, p) < dot(v, q);
    }

    T dist(Point p) {
        return abs(cross(v, p) - c) / len(v);
    }
};

Point a, b, c, d;

T SegDist(Point a, Point b, Point p)
{
    Line l(a, b);

    if (l.before(a, p) ^ l.before(b, p)) {
        return l.dist(p);
    }

    return min(len(p - a), len(p - b));
}

void solve(void)
{
    a.read();
    b.read();
    c.read();
    d.read();

    if (orient(a, b, c) * orient(a, b, d) < 0 &&
        orient(c, d, a) * orient(c, d, b) < 0) {
            printf("0.00\n");
            return;
        }

    T ans = min(SegDist(a, b, c), SegDist(a, b, d));
    ans = min(ans, SegDist(c, d, a));
    ans = min(ans, SegDist(c, d, b));

    printf("%.2lf\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}