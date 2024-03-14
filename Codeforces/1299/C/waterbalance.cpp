#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef long long T;

struct Point {
    T x, y;

    Point(void) {}
    Point(T a, T b) {x = a, y = b;}

    Point operator + (Point b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator * (T b) {
        return Point(x * b, y * b);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }
};

T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}
T orient(Point a, Point b, Point c)
{
    return cross(b - a, c - b);
}

int N;
vector<int> a;
vector<double> ans;
vector<double> pref;

vector<Point> points;
deque<Point> hull;

void find_hull(void)
{
    hull.pb(points[0]);
    hull.pb(points[1]);

    for (int i = 2; i <= N; i++) {
        while (hull.size() >= 2) {
            if (orient(hull[hull.size() - 2], hull.back(), points[i]) < 0)
                hull.pop_back();
            else
                break;
        }
        hull.push_back(points[i]);
    }
}

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    points.resize(N + 1);
    pref.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    points[0] = Point(0, 0);
    for (int i = 0; i < N; i++) {
        points[i + 1] = points[i] + Point(1, a[i]);
    }

    find_hull();

    double prev_val = 0;
    int prev_num = 0;
    for (int i = 0; i <= N; i++) {
        if (hull.front().x == i) {
            pref[i] = hull.front().y;
            hull.pop_front();
            prev_val = pref[i];
            prev_num = i;
        }
        else {
            pref[i] = prev_val + (hull.front().y - prev_val) / (hull.front().x - prev_num) * (i - prev_num);
        }
    }

    // Now build normal array
    ans.resize(N);
    for (int i = 0; i < N; i++)
        ans[i] = pref[i + 1] - pref[i];

    for (int i = 0; i < N; i++)
        printf("%.9lf\n", ans[i]);

    return 0;
}