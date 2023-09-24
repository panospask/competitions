#include <bits/stdc++.h>

using namespace std;

typedef double T;

struct Point {
    T x, y;

    Point(void) {
        x = y = 0;
    }
    Point(T a, T b) {
        x = a;
        y = b;
    }

    Point operator + (Point b) {
        return Point(x + b.x, y + b.y);
    }
    Point operator * (T k) {
        return Point(x * k, y * k);
    }
    Point operator - (Point b) {
        return *this + b * -1;
    }

    T len(void) {
        return sqrt(x * x + y * y);
    }
    Point unit(void) {
        return *this * (1 / len());
    }
};

T dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}
T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

struct Line {
    Point v;
    Point prp;
    T c;

    Line(T a, T b, T c) {
        v = Point(b, -a);
        this->c = -c;
    }
    Line(Point p, Point q) {
        v = q - p;
        c = cross(v, q);
    }
    Line(Point v, T c) {
        this->v = v;
        this->c = c;
    }

    void print(void) {
        printf("%lf %lf %lf\n", -v.y, v.x, -c);
    }

    // Shift line by k
    void shift(T k) {
        prp = Point(-v.y, v.x);
        T c_new = cross(v, prp.unit() * k) + c;
        c = c_new;
    }
};

int main(void)
{
    freopen("line3.in", "r", stdin);
    freopen("line3.out", "w", stdout);

    int A, B, C, R;
    scanf("%d %d %d %d", &A, &B, &C, &R);

    Line l(A, B, C);
    l.shift(R);
    l.print();
    l.shift(-2 * R);
    l.print();

    return 0;
}