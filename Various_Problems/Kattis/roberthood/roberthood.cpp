#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    double dist(Point b) {
        return sqrt(pow(this->x - b.x, 2.0) + pow(this->y - b.y, 2.0));
    }
};

bool operator == (Point a, Point b)
{
    return a.x == b.x && a.y == b.y;
}
Point operator - (Point a, Point b)
{
    return {a.x - b.x, a.y - b.y};
}

ll cross (Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

ll orient (Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

int n;
vector<Point> points;
vector<Point> Hull;
Point chosen = {0, INT_MAX};

bool sort_hull(Point a, Point b)
{
    if (a == chosen)
        return false;
    if (b == chosen)
        return true;

    int res = orient(chosen, a, b);
    if (res == 0)
        return chosen.dist(a) < chosen.dist(b);

    return res > 0;
}

int main(void)
{
    scanf("%d", &n);
    points.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
        if (points[i].y < chosen.y)
            chosen = points[i];
        else if (points[i].y == chosen.y && points[i].x > chosen.x)
            chosen = points[i];
    }
    sort(points.begin(), points.end(), sort_hull);

    Hull.push_back(chosen);
    for (int i = 0; i < n; i++) {
        Point p = points[i];
        if (p == chosen)
            break;

        while (Hull.size() >= 2) {
            if (orient(Hull[Hull.size() - 2], Hull.back(), p) <= 0)
                Hull.pop_back();
            else
                break;
        }

        Hull.push_back(p);
    }

    // Find the point with maximum distance from chosen
    n = Hull.size();
    int curpointer = 0;
    double d = -1;
    double globalmax = 0;

    for (int i = 0; i < n; i++) {
        Point p = Hull[i];
        d = p.dist(Hull[curpointer]);
        while (p.dist(Hull[(curpointer + 1) % n]) > d) {
            curpointer = (curpointer + 1) % n;
            d = p.dist(Hull[curpointer]);
        }

        globalmax = max(d, globalmax);
    }

    printf("%.6lf\n", globalmax);
    return 0;
}