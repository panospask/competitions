#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

struct Point {
    ll x, y;

    Point operator + (Point b) {
        return {this->x + b.x, this->y + b.y};
    }
    Point operator - (Point b) {
        return {this->x - b.x, this->y - b.y};
    }
    bool operator == (Point& b) {
        return this->x == b.x && this->y == b.y;
    }

    double dist(Point b) {
        return sqrt(pow(this->x - b.x, 2.0) + pow(this->y - b.y, 2.0));
    }
};

ll cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

ll dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

ll TriangleAreaDoubled(Point a, Point b, Point c)
{
    return abs(cross(b - a, c - a));
}

bool InTriangle(Point a, Point b, Point c, Point p)
{
    return TriangleAreaDoubled(a, b, c) == TriangleAreaDoubled(a, b, p) + TriangleAreaDoubled(a, c, p) + TriangleAreaDoubled(b, c, p);
}

ll orient(Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

// Returns true if a is clockwise from b with respect to c
bool counterclockwise(Point a, Point b, Point c)
{
    return orient(c, b, a) > 0;
}

int n;
vector<Point> HullPoints;
vector<Point> QueryPoints;
vector<Point> Hull;
Point chosen;

bool inAngle(Point a, Point b, Point c, Point p)
{
    return orient(b, c, p) >= 0 && orient(b, a, p) <= 0;
}

bool inSegment(Point a, Point b, Point p)
{
    return orient(a, b, p) == 0 && dot(a - p, b - p) <= 0;
}

bool inside_hull(Point p)
{
    if (inSegment(Hull.back(), chosen, p))
        return true;
    if (Hull.size() == 2 || !inAngle(Hull.back(), chosen, Hull[1], p))
        return false;

    // Binary search for the last point that is not counterclockwise from p (with respect to chosen)
    int l = 1;
    int r = Hull.size() - 1;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (counterclockwise(Hull[mid], p, chosen))
            r = mid;
        else
            l = mid;
    }

    return InTriangle(chosen, Hull[l], Hull[l + 1], p);
}

bool chosensort(Point a, Point b)
{
    if (a == chosen)
        return false;
    if (b == chosen)
        return true;
    if (orient(chosen, a, b) == 0)
        return chosen.dist(a) < chosen.dist(b);

    return orient(chosen, a, b) > 0;
}

int solve(void)
{
    chosen = {INT_MAX, INT_MAX};
    Hull.clear();
    for (int i = 0; i < HullPoints.size(); i++) {
        if (HullPoints[i].y < chosen.y)
            chosen = HullPoints[i];
        else if (HullPoints[i].y == chosen.y && HullPoints[i].x > chosen.x)
            chosen = HullPoints[i];
    }
    sort(HullPoints.begin(), HullPoints.end(), chosensort);

    Hull.push_back(chosen);

    for (int i = 0; i < HullPoints.size(); i++) {
        Point p = HullPoints[i];
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

    int ans = 0;
    for (auto q : QueryPoints)
        ans += inside_hull(q);

    return ans;
}

int main(void)
{
    freopen("curling.in", "r", stdin);
    freopen("curling.out", "w", stdout);

    scanf("%d", &n);
    HullPoints.resize(n);
    QueryPoints.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &HullPoints[i].x, & HullPoints[i].y);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &QueryPoints[i].x, &QueryPoints[i].y);
    }

    printf("%d ", solve());
    swap(HullPoints, QueryPoints);
    printf("%d\n", solve());

    return 0;
}