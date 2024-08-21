#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

const int REPS = 25;

struct Point {
    ld x, y;

    void read(void) {
        int x_i, y_i;
        scanf("%d %d", &x_i, &y_i);
        x = x_i;
        y = y_i;
    }
};

bool pointsort(Point& a, Point& b)
{
    if (a.x == b.x) {
        return a.y < b.y;
    }

    return a.x < b.y;
}

struct Line {
    // The current line is ax + b

    ld a, b;

    void make(Point p1, Point p2) {
        ;
    }
};

ld cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

ld intersect(Line l1, Line l2)
{
    return (l2.b - l1.b) / (l1.a - l2.a);
}

int N, K;
vector<Point> points;
Line west, east, north, south;
ld WALLS[4];
long long tot;

ld getArea(ld y)
{
    ld x = sqrt(1 - y*y);

    Line l;
    l.make({0, 0}, {x, y});

    ld x1 = intersect(l, east);
    ld x2 = intersect(l, south);
    ld x3 = intersect(l, west);
    ld x4 = intersect(l, north);

    ld ans = 0;
    if (x1 <= x2) {
        ;;
    }
}

int main(void)
{
    scanf("%d %d", &N, &K);

    if (N != 4) {
        exit(0);
    }

    points.resize(N);
    for (int i = 0; i < N; i++) {
        points[i].read();
    }

    sort(points.begin(), points.end(), pointsort);

    west.make(points[0], points[1]);
    east.make(points[2], points[3]);
    north.make(points[1], points[3]);
    south.make(points[0], points[2]);

    tot = (long long)(points[1].y - points[0].y) * (points[2].x - points[0].x);
    ld piece = (ld)tot / (K + 1);

    for (int i = 1; i <= K; i++) {
        ld target = piece * i;

        ld l = 0, r = 1;
        for (int i = 0; i < REPS; i++) {
            ;
        }
    }
}