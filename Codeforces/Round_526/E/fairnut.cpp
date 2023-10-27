#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
    int x;
    int y;
    ll a;
};

int N;
vector<Point> points;
deque<int> hull;
vector<ll> dp;

// Returns the intersection x of the line of i and the line of j
double intersect(int i, int j)
{
    return (double)(dp[i] - dp[j]) / (points[i].x - points[j].x);
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;

    points.resize(N + 1);
    dp.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        int x, y;
        ll v;
        cin >> x >> y >> v;
        points[i].x = x;
        points[i].y = y;
        points[i].a = v;
    }
    sort(points.begin() + 1, points.end(), [&] (const Point& a, const Point& b) {return a.x < b.x;});

    points[0] = {0, 0, 0};
    dp[0] = 0;

    hull.push_back(0);

    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        while (hull.size() > 1 && intersect(hull[0], hull[1]) >= points[i].y) {
            hull.pop_front();
        }

        dp[i] = (ll)points[i].x * points[i].y - points[i].a - (ll)points[i].y * points[hull[0]].x + dp[hull[0]];
        dp[i] = max(dp[i], dp[i - 1]);

        while (hull.size() > 1) {
            int sz = hull.size();
            if (intersect(hull[sz - 2], hull[sz - 1]) <= intersect(hull[sz - 1], i)) {
                hull.pop_back();
            }
            else {
                break;
            }
        }
        hull.push_back(i);
    }

    cout << dp[N] << endl;

    return 0;
}