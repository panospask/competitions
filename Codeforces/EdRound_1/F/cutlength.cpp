#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    Point(void) {}
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
    Point operator / (T b) {
        return *this * (1/b);
    }
};

T len(Point a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

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

    Line(void) {}
    Line(Point a, Point b) {
        v = b - a;
        c = cross(v, a);
    }

    T side(Point p) {
        return cross(v, p) - c;
    }
    bool online(Point p) {
        return side(p) == 0;
    }
};

// Check if line and segment intersect

int main(void)
{
    ;
}