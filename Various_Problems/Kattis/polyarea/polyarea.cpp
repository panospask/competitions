#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    Point operator - (Point b)
    {
        return {this->x - b.x, this->y - b.y};
    }
};

ll cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

// Area is positive if the path a -> b -> c turns CCW
ll SignedArea(Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

int n;
vector<Point> poly;

void solve(int t)
{
    n = t;
    poly.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &poly[i].x, &poly[i].y);

    Point chosen = {0, 0};
    ll TotalArea = 0;
    for (int i = 0; i < n; i++) {
        Point p1 = poly[i];
        Point p2 = poly[(i + 1) % n];

        TotalArea += SignedArea(chosen, p1, p2);
    }

    double res = (double) abs(TotalArea) / 2;

    if (TotalArea <= 0)
        printf("CW ");
    else
        printf("CCW ");

    printf("%.1lf\n", res);

    return;
}

int main(void)
{
    int t;
    for (scanf("%d", &t); t != 0; scanf("%d", &t))
        solve(t);
}