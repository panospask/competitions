#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef double T; 

const int REPS = 20;
const T EPS = 0.0000001;

struct Point {
    T x, y;
    T angle;

    int id = -1;

    void read(int i) {
        int x_i, y_i;
        scanf("%d %d", &x_i, &y_i);
        x = x_i;
        y = y_i;
        id = i;

        angle = atan2(y, x);
    }

    Point operator + (Point b) {
        return {this->x + b.x, this->y + b.y};
    }
    Point operator * (T b) {
        return {this->x * b, this->y * b};
    }
    Point operator - (Point b) {
        return *this + (b * -1);
    }
};

int N, K;
vector<Point> points;
vector<T> A, B, C;
vector<pair<T, T>> ans;

bool anglesort(const Point& a, const Point& b)
{
    return a.angle < b.angle;
}

// Compute the area of the polygon that lies under the line with given angle
T area(T angle, int p)
{
    return abs(tan(angle) * A[p] + B[p] - tan(M_PI_2 - angle) * C[p]);
}

int main(void)
{
    scanf("%d %d", &N, &K);

    points.resize(N);
    A.resize(N);
    B.resize(N);
    C.resize(N);
    ans.resize(K);

    for (int i = 0; i < N; i++) {
        points[i].read(i);
    }

    sort(points.begin(), points.end(), anglesort);

    for (auto p : points) {
        int mod = p.id % 2 ? 1 : -1;

        A[0] += p.x * p.x * mod;
    }
    for (int i = 0; i < points.size(); i++) {
        auto p = points[i];
        int mod = p.id % 2 ? 1 : -1;

        if (i) {
            A[i] = A[i - 1];
            B[i] = B[i - 1];
            C[i] = C[i - 1];
        }

        A[i] -= p.x * p.x / 2 * mod;
        B[i] += p.x * p.y * mod;
        C[i] += p.y * p.y / 2 * mod;
    }

    T total_area = area(atan2(points.back().y, points.back().x), N - 1);
    T cut = total_area / (K + 1);
    T target = cut;

    for (int p = 1; p < points.size() && target < total_area; p++) {
        T sta = atan2(points[p - 1].y, points[p - 1].x);
        T en = atan2(points[p].y, points[p].x);
        T ol = area(en, p - 1);

        while (target < total_area && ol > target) {
            T l = sta;
            T r = en;

            for (int i = 0; i < REPS; i++) {
                T mid = (l + r) / 2;
                if (area(mid, p - 1) < target) {
                    l = mid;
                }
                else {
                    r = mid;
                }
            }

            T x = sqrt(1 / (1 + tan(r) * tan(r)));
            T y = sqrt(1 - x * x);
            target += cut;

            printf("%.8lf %.8lf\n", (double)x, (double)y);
        }
    }

    return 0;
}