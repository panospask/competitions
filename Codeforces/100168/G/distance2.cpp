#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    Point(void) {
        x = y = 0;
    }
    Point(T a, T b) {
        x = a;
        y = b;
    }

    Point operator + (Point b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator * (T b) {
        return Point(x * b, y * b);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    T abs(void) {
        return sqrt(x * x + y * y);
    }
};

T dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}
T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

struct Line {
    Point v;
    T c;

    Line(Point a, Point b) {
        v = b - a;
        c = cross(v, a);
    }

    T side(Point p) {
        return cross(v, p) - c;
    }
    T dist(Point p) {
        return abs(side(p)/v.abs());
    }
};

int main(void)
{
    freopen("distance2.in", "r", stdin);
    freopen("distance2.out", "w", stdout);

    int x, y, a, b, c, d;
    scanf("%d %d %d %d %d %d", &x, &y, &a, &b, &c, &d);

    Line l(Point(a, b), Point(c, d));

    printf("%.6lf\n", l.dist(Point(x, y)));
}