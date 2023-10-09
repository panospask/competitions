#include <bits/stdc++.h>

using namespace std;

typedef long long T;

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

    void read(void) {
        int a, b;
        scanf("%d %d", &a, &b);

        x = a;
        y = b;
    }
};

T sqlen(Point a)
{
    return a.x * a.x + a.y * a.y;
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

bool ysort(Point& a, Point& b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

Point piv;
bool pivotsort(Point& a, Point& b)
{
    if (orient(piv, a, b) == 0)
        return sqlen(a - piv) < sqlen(b - piv);

    return orient(piv, a, b) > 0;
}

int N;
vector<Point> points;

int ans = 0;

void process_point(int i)
{
    piv = points[i];
    sort(points.begin() + i + 1, points.end(), pivotsort);

    int loc = 2;
    int res = 2;
    for (int j = i + 2; j < N; j++) {
        if (orient(points[i], points[j - 1], points[j]) == 0) {
            loc++;
        }
        else {
            loc = 2;
        }

        res = max(loc, res);
    }

    ans = max(ans, res);
    sort(points.begin(), points.end(), ysort);
}

void solve(void)
{
    points.resize(N);
    for (int i = 0; i < N; i++)
        points[i].read();

    ans = min(N, 2);

    sort(points.begin(), points.end(), ysort);
    for (int i = 0; i < N - 1; i++)
        process_point(i);

    printf("%d\n", ans);
}

int main(void)
{
    scanf("%d", &N);
    while (N) {
        solve();
        scanf("%d", &N);
    }

    return 0;
}