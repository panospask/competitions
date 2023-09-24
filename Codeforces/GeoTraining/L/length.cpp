#include <bits/stdc++.h>

using namespace std;

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
    Point operator * (T c) {
        return Point(x * c, y * c);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    T sqlen(void) {
        return x * x + y * y;
    }
    double len(void) {
        return sqrt(sqlen());
    }
};

Point p;
Point q;

int main(void)
{
    freopen("length.in", "r", stdin);
    freopen("length.out", "w", stdout);

    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    p = Point(a, b);
    q = Point(c, d);

    Point v = q - p;
    printf("%lf\n", v.len());

    return 0;
}