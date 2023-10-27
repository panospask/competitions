#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef ll T;

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
    return cross(b - a, c - a);
}

int N;
deque<Point> hull;
vector<Point> points;
vector<double> ans;

void find_hull(void)
{
    hull.pb(points[0]);
    hull.pb(points[1]);

    for (int i = 2; i < points.size(); i++) {
        while (hull.size() > 1) {
            if (orient(hull[hull.size() - 2], hull.back(), points[i]) >= 0)
                hull.pop_back();
            else
                break;
        }
        hull.pb(points[i]);
    }
}

int main(void)
{
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);

    scanf("%d", &N);

    points.pb(Point(0, 0));
    for (int i = 1; i <= N; i++) {
        int f;
        scanf("%d", &f);
        points.pb(Point(i, f));
    }
    points.pb(Point(N + 1, 0));

    find_hull();

    ans.resize(N + 2);

    ll p_val = 0;
    int p_num = 0;
    for (int i = 0; i <= N + 1; i++) {
        if (hull.front().x == i) {
            ans[i] = hull.front().y * (ll)1e5;
            p_val = hull.front().y;
            p_num = i;

            hull.pop_front();
        }
        else {
            ans[i] = ((hull.front().y - p_val) * (i - p_num)  * 1e5 / (double)(hull.front().x - p_num) + p_val * 1e5);
        }
    }

    for (int i = 1; i <= N; i++) {
        ll v = ans[i];
        printf("%lld\n", v);
    }

    return 0;
}