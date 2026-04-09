#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long T;

struct Point {
    T x, y;

    Point(T a, T b) {
        x = a;
        y = b;
    }
    Point(void) {
        x = y = 0;
    }

    Point operator + (Point b) {
        return Point(this->x + b.x, this->y + b.y);
    }
    Point operator * (T b) {
        return Point(this->x * b, this->y * b);
    }
    Point operator - (Point b) {
        return *this + (b * -1);
    }

    void read(void) {
        scanf("%lld %lld", &x, &y);
    }
};

int N;
Point chosen = {0, 0};
vector<Point> points;
vector<int> remaining;
vector<int> Hull;
vector<int> perm;

T cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
T orient(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

bool sort_by_angle(int a, int b) {
    if (points[a].x == chosen.x && points[a].y == chosen.y) {
        return true;
    }
    if (points[b].x == chosen.x && points[b].y == chosen.y) {
        return false;
    }
    T res = orient(chosen, points[a], points[b]);

    return res > 0;
}

bool inside(vector<int>& v, int x) {
    int pos = lower_bound(v.begin(), v.end(), x) - v.begin();
    if (pos == v.size() || v[pos] != x) {
        return false;
    }
    return true;
}

void findHull(void) {
    N = remaining.size();
    Hull.clear();

    sort(remaining.begin(), remaining.end(), sort_by_angle);
    

    for (int i = 0; i < remaining.size(); i++) {
        Point cur = points[remaining[i]];
        while (Hull.size() >= 2) {
            int p1 = Hull[Hull.size() - 2];
            int p2 = Hull[Hull.size() - 1];

            if (orient(points[p1], points[p2], cur) <= 0) {
                Hull.pop_back();
            }
            else {
                break;
            }
        }
        Hull.push_back(remaining[i]);
    }
    chosen = points[remaining.back()];

    for (int i = 0; i < Hull.size(); i++) {
        perm.push_back(Hull[i]);
    }
    sort(Hull.begin(), Hull.end());

    vector<int> newrem;
    for (int i = 0; i < remaining.size(); i++) {
        if (!inside(Hull, remaining[i])) {
            newrem.push_back(remaining[i]);
        }
    }
    swap(remaining, newrem);
}

void solve(void) {
    scanf("%d", &N);

    points.resize(N);
    remaining.resize(N);
    perm.clear();
    
    for (int i = 0; i < N; i++) {
        points[i].read();
        remaining[i] = i;
    }

    chosen = points[remaining[0]];
    for (int i = 0; i < remaining.size(); i++) {
        if (points[remaining[i]].x < chosen.x) {
            chosen = points[remaining[i]];
        }
    }

    while (remaining.size()) {
        findHull();
    }

    for (int i = 0; i < perm.size(); i++) {
        printf("%d ", perm[i] + 1);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}