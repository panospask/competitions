#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    Point(void) {};
    Point(T a, T b) {x = a; y = b;}

    Point operator + (Point b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator * (T b) {
        return Point(x * b, y * b);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    T len(void) {
        return sqrt(x * x + y * y);
    }

    void read(void) {
        int a, b;
        scanf("%d %d", &a, &b);

        x = a;
        y = b;
    }
};

T len(Point a)
{
    return a.len();
}

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
    return cross(b - a, c - a);
}

struct Line {
    Point v;
    T c;

    Line(Point p, Point q) {
        v = q - p;
        c = cross(v, q);
    }

    // Returns true if the projection of a to l appears before the projection of b to l
    // in the direction of v
    bool LineCompare(Point a, Point b) {
        return dot(v, a) < dot(v, b);
    }

    T dist(Point p) {
        return abs(cross(v, p) - c) / v.len();
    }
};

struct Segment {
    Point a, b;

    bool differ(Segment t) {
        return orient(a, b, t.a) * orient(a, b, t.b) < 0;
    }
};

bool proper_intersect(Segment s, Segment t)
{
    return s.differ(t) && t.differ(s);
}

bool on_segment(Point p, Segment s)
{
    return (dot(s.a - p, s.b - p) >= 0) && (orient(s.a, s.b, p) == 0);
}

T point_distance(Point p, Segment s)
{
    if (on_segment(p, s))
        return 0;

    Line l(s.a, s.b);

    if (l.LineCompare(s.a, p) ^ l.LineCompare(s.b, p))
        return l.dist(p);

    return min(len(p - s.a), len(p - s.b));
}

T segment_distance(Segment s, Segment t)
{
    if (proper_intersect(s, t))
        return 0;

    T m1 = min(point_distance(s.a, t), point_distance(s.b, t));
    T m2 = min(point_distance(t.a, s), point_distance(t.b, s));

    return min(m1, m2);
}

Segment s, t;

int main(void)
{
    freopen("distance5.in", "r", stdin);
    freopen("distance5.out", "w", stdout);

    s.a.read();
    s.b.read();
    t.a.read();
    t.b.read();

    printf("%.6lf\n", segment_distance(s, t));

    return 0;
}