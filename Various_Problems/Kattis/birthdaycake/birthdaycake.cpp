#include <bits/stdc++.h>

using namespace std;

typedef double T;

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
    Point operator / (T b) {
        return *this * (1 / b);
    }

    void read(void) {
        int a, b;
        scanf("%d %d", &a, &b);
        x = a;
        y = b;
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
    T c;

    Line(void) {};
    Line(T k, T l, T m) {
        v = Point(l, -k);
        c = -m;
    }

    T side(Point p) {
        return cross(v, p) - c;
    }
};

int N, M, R;
vector<Point> candles;
vector<Line> lines;

int main(void)
{
    scanf("%d %d %d", &N, &M, &R);

    candles.resize(N);
    lines.resize(M);
    for (int i = 0; i < N; i++)
        candles[i].read();
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);

        lines[i] = Line(a, b, c);
    }

    int pieces = 1;
    for (int i = 0; i < M; i++) {
        int crossed = 0;
        for (int j = i + 1; j < M; j++) {
            // Check for i, j intersection inside
            if (cross(lines[i].v, lines[j].v) == 0)
                continue;

            Point inter = (lines[j].v * lines[i].c - lines[i].v * lines[j].c);
            inter = inter / cross(lines[i].v, lines[j].v);

            if (inter.x * inter.x + inter.y * inter.y < R * R)
                crossed++;
        }

        pieces += crossed + 1;
    }

    if (pieces != N) {
        printf("no\n");
        return 0;
    }

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++) {
            bool found = false;

            for (int k = 0; k < M; k++)
                found = found || ((lines[k].side(candles[i])) * lines[k].side(candles[j]) < 0);

            if (!found) {
                printf("no\n");
                return 0;
            }
        }

    printf("yes\n");

    return 0;
}