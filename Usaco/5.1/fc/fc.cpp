/*
ID: panos.p1
LANG: C++11
TASK: fc
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 10000

using namespace std;

struct point {
    double x;
    double y;
};
typedef struct point Point;

Point operator - (Point a, Point b)
{
    a.x -= b.x;
    a.y -= b.y;

    return a;
}

double crossprod (Point a, Point b)
{
    return a.x * b.y - a.y* b.x;
}

// Positive direction = left turn, Negative direction = right turn
int direction (Point a, Point b, Point c)
{
    // Do we turn left or right at b??

    Point v1 = b - a;
    Point v2 = c - a;

    double result = crossprod(v1, v2);
    if (result > 0)
        return 1;
    else if (result < 0)
        return -1;
    else 
        return 0;
}
double dist(double a, double b)
{
    double ans = a - b;
    if (ans < 0)
        ans *= -1;
    
    return ans;
}

double dist(Point a, Point b)
{
    return sqrt(pow(dist(a.x, b.x), 2) + pow(dist(a.y, b.y), 2));
}


int n;
double length;
Point points[MAXN];
Point origin;
vector<Point> sorted;

bool operator < (Point a, Point b)
{
    int ans = direction(origin, a, b);

    if (ans > 0)
        return true;
    return false;
}

int main(void)
{
    freopen("fc.in", "r", stdin);
    freopen("fc.out", "w", stdout);

    scanf("%d", &n);
    int lmost_point = 0;    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
        if (points[i].y < points[lmost_point].y)
            lmost_point = i;
        else if (points[i].y == points[lmost_point].y && points[i].x < points[lmost_point].x)
            lmost_point = i;
    }

    origin = points[lmost_point];
    swap(points[lmost_point], points[n-1]);
    sort(points, points + n - 1);

    Point curpoint;
    sorted.pb(points[0]);
    for (int i = 1; i < n - 1; i++) {
        curpoint = points[i];

        if (direction(origin, sorted.back(), curpoint) != 0)
            sorted.pb(curpoint);
        else {
            if (dist(origin, curpoint) > dist(origin, sorted.back())) {
                sorted.pop_back();
                sorted.pb(curpoint);
            }
        }
    }

    vector<Point> hull;
    // Points sorted, time for convex hull
    hull.pb(origin);
    hull.pb(sorted[0]);
    hull.pb(sorted[1]);

    for (int i = 2; i < sorted.size(); i++) {
        curpoint = sorted[i];

        while (direction(hull[hull.size() - 2], hull[hull.size() - 1], curpoint) <= 0)
            hull.pop_back(); // Makes a nonleft turn --> the middle point can be skipped
        hull.pb(curpoint);
    }   

    // Find the total distance as a sum of the individual ones between hull neighbours
    double ttl_dist = 0;
    for (int i = 1; i < hull.size(); i++)
        ttl_dist += dist(hull[i-1], hull[i]);
    ttl_dist += dist(hull[hull.size() -1], hull[0]);

    printf("%.2lf\n", ttl_dist);
    return 0;
}