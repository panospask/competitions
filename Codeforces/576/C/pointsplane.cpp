#include <bits/stdc++.h>

using namespace std;

const int BLOCK_SIZE = 1000;
const int MAXC = 1e6;

typedef pair<int, int> pi;

struct Point {
    int x;
    int y;
    int id;
};

int N;
vector<Point> points;

bool mosort(const Point& a, const Point& b)
{
    if (a.x / BLOCK_SIZE == b.x / BLOCK_SIZE) {
        bool good = a.y < b.y;
        if (BLOCK_SIZE % 2)
            good = !good;

        return good;
    }

    return a.x / BLOCK_SIZE < b.x / BLOCK_SIZE;
}

int main(void)
{
    scanf("%d", &N);

    points.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        points[i].x--;
        points[i].y--;
        points[i].id = i;
    }

    sort(points.begin(), points.end(), mosort);

    for (auto p : points)
        printf("%d ", p.id + 1);
    printf("\n");

    return 0;
}