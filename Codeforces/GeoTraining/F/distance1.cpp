#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    Point (T a, T b) {
        x = a;
        y = b;
    }
    Point (void) {
        x = y = 0;
    }

    Point operator + (Point b) {
        return Point(this->x + b.x, this->y + b.y);
    }
    Point operator * (T c) {
        return Point(x * c, y * c);
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

T dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

T sq(Point p)
{
    return p.x * p.x + p.y * p.y;
}

T abs(Point p)
{
    return sqrt(sq(p));
}

struct Line {
    Point v;
    T c;

    Line(T a, T b, T c) {
        v = Point(b, -a);
        this->c = -c;
    }
    Line(Point p, Point q) {
        v = q - p;
        this->c = cross(v, q);
    }
    Line(void) {
        ;
    }

    T side(Point p) {
        return cross(v, p) - c;
    }

    T dist(Point p) {
        return abs(side(p) / abs(v));
    }

    bool inLine(Point p) {
        return side(p) == 0;
    }
};

int a, b, c;
Point p;
Line l;

int main(void)
{
    freopen("distance1.in", "r", stdin);
    freopen("distance1.out", "w", stdout);

    p.read();
    scanf("%d %d %d", &a, &b, &c);

    l = Line(a, b, c);

    printf("%lf\n", l.dist(p));

    return 0;
}