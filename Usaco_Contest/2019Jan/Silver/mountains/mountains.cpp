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
vector<pair<int, int>> basecoords;
int n;

bool comppair(pair<int, int> a, pair<int, int> b)
{
    if (a.first == b.first)
        return a.second > b.second;

    return a.first < b.first;
}

int main(void)
{
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);

    scanf("%d", &n);
    Point p;
    int lbasecoord, rbasecoord;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p.x, &p.y);
        pointcoords.pb(p);

        lbasecoord = p.x - p.y;
        rbasecoord = lbasecoord + 2 * p.y;

        basecoords.pb(mp(lbasecoord, rbasecoord));
    }

    // Sort by leftmost base point
    sort(basecoords.begin(), basecoords.end(), comppair);

    int rightmost_coord = INT_MIN;
    int mt_seen = 0;

    for (auto coords : basecoords) {
        if (rightmost_coord == INT_MIN) {
            rightmost_coord = coords.second;
            mt_seen ++;
        }
        else if (coords.second > rightmost_coord) {
            rightmost_coord = coords.second;
            mt_seen++;
        }
    }

    printf("%d\n", mt_seen);
    return 0;
}