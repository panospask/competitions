/*
ID: panos.p1
LANG: C++11
TASK: rect1
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXCOORD 10000

using namespace std;

typedef pair<int, int> ii;

struct rect {
    int x1, y1, x2, y2, colour;

    rect(int a, int b, int c, int d, int e) {
        this->x1 = a;
        this->y1 = b;
        this->x2 = c;
        this->y2 = d;
        this->colour = e;
    }
    rect(void) {
        ;
    }

    int area(void) {
        return (this->x2 - this->x1) * (this->y2 - this->y1);
    }
};
typedef struct rect Rect;

vector<Rect> placed;
stack<Rect> to_place;
int n;
int a, b;
unordered_map<int, int> colval;
set<ii> vals;

bool check_overlap(Rect& a, Rect& b)
{
    if (a.x1 >= b.x2 || b.x1 >= a.x2 || a.y1 >= b.y2 || b.y1 >= a.y2)
        return false;

    return true;
}

int getArea(Rect a, int ind)
{
    int i = ind;
    while (i < placed.size() && !check_overlap(a, placed[i]))
        i++;

    if (i == placed.size()) // No overlaps found
        return a.area();

    int area = 0;
    Rect cur;
    if (a.x1 < placed[i].x1) {
        cur = Rect(a.x1, a.y1, placed[i].x1, a.y2, a.colour);
        area += getArea(cur, i + 1);
        a.x1 = placed[i].x1;
    }
    if (a.y1 < placed[i].y1) {
        cur = Rect(a.x1, a.y1, a.x2, placed[i].y1, a.colour);
        area += getArea(cur, i + 1);
        a.y1 = placed[i].y1;
    }
    if (a.x2 > placed[i].x2) {
        cur = Rect(placed[i].x2, a.y1, a.x2, a.y2, a.colour);
        area += getArea(cur, i + 1);
        a.x2 = placed[i].x2;
    }
    if (a.y2 > placed[i].y2) {
        cur = Rect(a.x1, placed[i].y2, a.x2, a.y2, a.colour);
        area += getArea(cur, i + 1);
        a.y2 = placed[i].y2;
    }

    return area;
}

int main(void)
{
    freopen("rect1.in", "r", stdin);
    freopen("rect1.out", "w", stdout);

    scanf("%d %d %d", &a, &b, &n);
    int x1, y1, x2, y2, col;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &col);

        to_place.push(Rect(x1, y1, x2, y2, col));
        colval[col] = 0;
    }   

    Rect cur;
    while (!to_place.empty()) {
        cur = to_place.top(); to_place.pop();
        colval[cur.colour] += getArea(cur, 0);
        placed.pb(cur);
    }

    // Place the white underneath all recs
    cur = Rect(0, 0, a, b, 1);
    colval[1] += getArea(cur, 0);

    for (auto val : colval)
        vals.insert(val);

    for (auto val : vals)
        if (val.second != 0)
            printf("%d %d\n", val.first, val.second);

    return 0;
}