#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;
    Point(void) {};
    Point(T a, T b) {this->x = a; this->y = b;}

    Point operator + (const Point& b) {
        return Point(this->x + b.x, this->y + b.y);
    }
    Point operator * (const T c) {
        return Point(this->x * c, this->y * c);
    }
    Point operator - (Point b) {
        return *this + (b * -1.0);
    }
    Point operator / (T c) {
        return *this * (1/c);
    }
};

bool operator < (const Point& a, const Point& b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

struct Segment {
    Point f;
    Point s;

    Segment(void) {}
    Segment(Point i, Point j) {f = min(i, j); s = max(i, j);}
};

T dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}
T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

T orient(Point a, Point b, Point c)
{
    T res = cross(b - a, c - a);
    return res;
}

bool colinear(Segment a, Segment b)
{
    return cross(a.s - a.f, b.s - b.f) == 0;
}

bool intersect_proper(Segment a, Segment b, Point& out)
{
    T oc = orient(a.f, a.s, b.f);
    T od = orient(a.f, a.s, b.s);
    T oa = orient(b.f, b.s, a.f);
    T ob = orient(b.f, b.s, a.s);

    if (oc * od < 0 && oa * ob < 0) {
        out = (a.f * ob - a.s * oa) / (ob - oa);
        return true;
    }

    return false;
}

bool colinear(Point a, Point b, Point c)
{
    return cross(c - b, c - a) == 0;
}

bool inDisk(Point a, Point b, Point p)
{
    return dot(a - p, b - p) <= 0;
}

bool onSegment(Point a, Point b, Point p)
{
    return inDisk(a, b, p) && orient(a, b, p) == 0;
}

int n;
int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        Point a, b, c, d;
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);

        Point out;
        if (intersect_proper(Segment(a, b), Segment(c, d), out)) {
            if (out.x == 0)
                out.x = +0;
            if (out.y == 0)
                out.y = +0;
            printf("%.2lf %.2lf\n", out.x, out.y);
            continue;
        }

        set<Point> pts;
        if (onSegment(c, d, a)) pts.insert(a);
        if (onSegment(c, d, b)) pts.insert(b);
        if (onSegment(a, b, c)) pts.insert(c);
        if (onSegment(a, b, d)) pts.insert(d);

        if (pts.empty())
            printf("none\n");
        else {
            for (auto p : pts) {
                if (p.x == 0)
                    p.x = +0;
                if (p.y == 0)
                    p.y = +0;
                printf("%.2lf %.2lf ", p.x, p.y);
            }
            printf("\n");
        }
    }

    return 0;
}