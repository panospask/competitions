#include <bits/stdc++.h>

using namespace std;

typedef long long PointType;

struct Point {
    PointType x, y;

    Point (PointType a, PointType b) {
        x = a;
        y = b;
    }
    Point (void) {
        x = 0;
        y = 0;
    }

    Point operator + (Point b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator * (PointType c) {
        return Point(x * c, y * c);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    void print(void) {
        printf("%lld %lld\n", x, y);
    }
};

// The following functions (dot and cross) treat points as 2d vectors with start at (0, 0)

PointType dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

PointType cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

// 1 if c is to left of line ab, 0 if it is on the line, -1 if it is on the right
int Orient(Point a, Point b, Point c)
{
    // Essentially AB x AC
    PointType res = cross(b - a, c - a);
    if (res > 0)
        return 1;
    else if (res < 0)
        return -1;

    return 0;
}

// A point in the line in which the sorting begins
Point v(-1, 0);

// Returns true if p is in the second half of the points to be sorted
bool SecondHalf(Point p)
{
    if (p.y > 0 || (p.y == 0 && p.x < 0))
        return true;

    return false;
}

bool PolarSort(Point a, Point b)
{
    if (a.x == 0 && a.y == 0) {
        return SecondHalf(b);
    }
    if (b.x == 0 && b.y == 0) {
        return !SecondHalf(a);
    }

    if (SecondHalf(a) == SecondHalf(b)) {
        PointType res = Orient(Point(0, 0), a, b);
        if (res > 0)
            return true;
        if (res < 0)
            return false;

        return a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y;
    }

    return SecondHalf(a) < SecondHalf(b);
}

int N;
vector<Point> points;

int main(void)
{
    scanf("%d", &N);

    points.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%lld %lld", &points[i].x, & points[i].y);
    }

    sort(points.begin(), points.end(), PolarSort);

    for (int i = 0; i < N; i++)
        points[i].print();

    return 0;
}