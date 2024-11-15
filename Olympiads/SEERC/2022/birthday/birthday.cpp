#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long T;

struct Point {
    T x, y;

    void read(void) {
        double a, b;
        scanf("%lf %lf", &a, &b);

        x = a * 1e6;
        y = b * 1e6;
    }

    Point operator + (Point b) {
        return {x + b.x, y + b.y};
    }
    Point operator * (T k) {
        return {x * k, y * k};
    }
    Point operator - (Point b) {
        return *this + b * (-1);
    }

    bool operator == (Point b) {
        return x == b.x && y == b.y;
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


Point pivot;
bool pivotsort(Point a, Point b)
{
    if (b == pivot) {
        return false;
    }
    if (a == pivot) {
        return true;
    }

    return orient(pivot, a, b) > 0;
}

int N, M;
vector<Point> chocolates;
vector<Point> strawberries;

void special(void)
{
    pivot = strawberries[0];

    vector<Point> s1, s2;
    for (auto p : chocolates) {
        if (p.x > pivot.x) {
            s1.pb(p);
        }
        else if (p.x < pivot.x) {
            s2.pb(p);
        }
        else if (p.y < pivot.y) {
            s1.pb(p);
        }
        else {
            s2.pb(p);
        }
    }

    sort(s1.begin(), s1.end(), pivotsort);
    sort(s2.begin(), s2.end(), pivotsort);

    int ans = 0;
    int k = 0;
    for (int j = 0; j < s1.size(); j++) {
        while (k < s2.size() && orient(s1[j], pivot, s2[k]) <= 0) {
            k++;
        }

        ans = max(ans, j + 1 + (int)s2.size() - k);
    }

    k = 0;
    for (int j = 0; j < s2.size(); j++) {
        while (k < s1.size() && orient(s2[j], pivot, s1[k]) < 0) {
            k++;
        }

        ans = max(ans, (int)s2.size() - j + k);
    }

    k = 0;
    for (int j = 0; j < s1.size(); j++) {
        while (k < s2.size() && orient(s1[j], pivot, s2[k]) < 0) {
            k++;
        }

        ans = max(ans, (int)s1.size() - j + k);
    }

    for (int j = 0; j < s2.size(); j++) {
        while (k < s1.size() && orient(s2[j], pivot, s1[k]) <= 0) {
            k++;
        }

        ans = max(ans, j + 1 + (int)s1.size() - k);
    }

    printf("%d\n", ans);
    exit(0);
}

int main(void)
{
    scanf("%d %d", &N, &M);

    chocolates.resize(N);
    strawberries.resize(M);

    for (int i = 0; i < N; i++) {
        chocolates[i].read();
    }

    int mx = 0;
    for (int i = 0; i < M; i++) {
        strawberries[i].read();

        if (strawberries[i].x < strawberries[mx].x) {
            mx = i;
        }
    }

    if (strawberries.size() == 1) {
        special();
    }

    pivot = strawberries[mx];
    sort(strawberries.begin(), strawberries.end(), pivotsort);

    vector<Point> hull;
    for (int i = 0; i < M; i++) {
        while (hull.size() > 2) {
            int l = hull.size() - 1;

            if (orient(hull[l - 1], hull[l], strawberries[i]) <= 0) {
                hull.pop_back();
            }
            else {
                break;
            }
        }
        hull.pb(strawberries[i]);
    }

    hull.pb(hull[0]);
    hull.pb(hull[1]);

    int ans = 0;
    for (int i = 1; i < hull.size() - 1; i++) {
        Point p1 = hull[i - 1];
        Point p2 = hull[i];
        Point p3 = hull[i + 1];

        vector<Point> s1, s2;
        int cur = 0;

        for (auto p : chocolates) {
            T v1 = orient(p1, p2, p);
            T v2 = orient(p3, p2, p);

            if (v1 >= 0) {
                if (v2 > 0) {
                    s1.pb(p);
                }
            }
            else {
                if (v2 > 0) {
                    cur++;
                }
                else {
                    s2.pb(p);
                }
            }
        }

        pivot = p2;
        sort(s1.begin(), s1.end(), pivotsort);
        sort(s2.begin(), s2.end(), pivotsort);

        int k = 0;
        for (int j = 0; j < s1.size(); j++) {
            while (k < s2.size() && orient(s1[j], pivot, s2[k]) <= 0) {
                k++;
            }

            ans = max(ans, cur + j + 1 + (int)s2.size() - k);
        }

        k = 0;
        for (int j = 0; j < s2.size(); j++) {
            while (k < s1.size() && orient(s2[j], pivot, s1[k]) < 0) {
                k++;
            }

            ans = max(ans, cur + (int)s2.size() - j + k);
        }
    }

    printf("%d\n", ans);

    return 0;
}