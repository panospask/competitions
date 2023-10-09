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
        return Point(x * b, y * b);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    T abs(void) {
        return sqrt(x * x + y * y);
    }
};

T dot(Point p, Point q)
{
    return p.x * q.x + p.y * q.y;
}
T cross(Point p, Point q)
{
    return p.x * q.y - p.y * q.x;
}

struct Line {
    Point v;
    T c;

    Line(Point a, Point b) {
        v = b - a;
        c = cross(v, a);
    }

    // Returns true if, while travelling in the direction of v on the line, you pass p before q
    // If p or q are points not on the line, then the orthagonal projections are taken
    bool before(Point p, Point q) {
        return dot(v, p) < dot(v, q);
    }

    T side(Point p) {
        return cross(v, p) - c;
    }
    T dist(Point p) {
        return abs(side(p)) / v.abs();
    }
};

Point P;
Point A, B;

T absolut(Point a)
{
    return a.abs();
}

double SegDist(Point P)
{
    Line l(A, B);

    if (l.before(A, P) ^ l.before(B, P)) {
        // Inside the segments endpoints
        return l.dist(P);
    }

    return min(absolut(A - P), absolut(B - P));
}

int main(void)
{
    freopen("distance4.in", "r", stdin);
    freopen("distance4.out", "w", stdout);

    int m, n, l, o, p, q;
    scanf("%d %d %d %d %d %d", &m, &n, &l, &o, &p, &q);
    P = Point(m, n);
    A = Point(l, o);
    B = Point(p, q);

    printf("%.6lf\n", SegDist(P));
}