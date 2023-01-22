#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

struct point {
    int x, y;
};
typedef struct point Point;

bool operator < (Point a, Point b) 
{
    if (a.y == b.y)
        return a.x < b.x;
    else 
        return a.y < b.y;
}

bool xcomp(Point p, Point q) 
{
    if (p.x == q.x)
        return p.y < q.y;
    return p.x < q.x;
}

vector<Point> pointcoords;
int n;

int main(void)
{
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);

    scanf("%d", &n);
    Point p;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p.x, &p.y);
        pointcoords.pb(p);
    }
    sort(pointcoords.rbegin(), pointcoords.rend());

    int seen_points = 0;

    // Calculate the highest point
    int curpoint = 0;
    int xcoord = pointcoords[curpoint].x, ycoord = pointcoords[curpoint].y;
    seen_points++;
    int a = pointcoords[curpoint].x - pointcoords[curpoint].y;
    int b = pointcoords[curpoint].y + pointcoords[curpoint].x;

    int cur_a, cur_b;
    for (int i = 0; i < n; i++) {
        cur_a = pointcoords[i].x - pointcoords[i].y;
        cur_b = pointcoords[i].y + pointcoords[i].x;

        if (cur_a < a) {
            seen_points++;
            a = cur_a;
        }
        else if (cur_b > b) {
            seen_points++;
            b = cur_b;
        }
    }

    printf("%d\n", seen_points);
    return 0;
}