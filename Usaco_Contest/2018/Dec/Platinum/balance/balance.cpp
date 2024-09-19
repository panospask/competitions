#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll MUL = 1e5;

struct Point {
    int x, y;

    Point operator + (Point b) {
        return {this->x + b.x, this->y + b.y};
    }
    Point operator * (int b) {
        return {x * b, y * b};
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }
};

ll cross(Point a, Point b)
{
    return (ll)a.x * b.y - (ll)a.y * b.x;
}

// Returns true if, when traveling from a to b, c is to the right
bool isright(Point a, Point b, Point c)
{
    return cross(b - a, c - b) < 0;
}

int N;
vector<int> f;
vector<Point> points;
vector<ll> ans;

int main(void)
{
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);

    scanf("%d", &N);

    f.resize(N + 2);
    points.resize(N + 2);
    
    f[0] = 0;
    points[0] = {0, 0};
    for (int i = 1; i <= N; i++) {
        scanf("%d", &f[i]);
        points[i] = {i, f[i]};
    }
    points[N + 1] = {N + 1, 0};

    vector<Point> hull;
    hull.pb(points[0]);

    for (int i = 1; i <= N + 1; i++) {
        while (hull.size() >= 2) {
            int sz = hull.size();
            if (!isright(hull[sz - 2], hull[sz - 1], points[i])) {
                hull.pop_back();
            }
            else {
                break;
            }
        }

        hull.pb(points[i]);
    }

    ans.resize(N + 2);
    int p = 0;
    Point prv;
    for (int i = 0; i <= N + 1; i++) {
        Point cur = hull[p];
        if (cur.x == i) {
            ans[i] = (ll)cur.y * MUL;
            prv = cur;
            p++;
        }
        else {
            ans[i] = (ll)cur.y * (i - prv.x) + (ll)prv.y * (cur.x - i);
            ans[i] = ans[i] * MUL / (cur.x - prv.x);
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}