#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long T;

struct Point {
    T x, y;
    int id;

    Point operator + (const Point& b) {
        return {this->x + b.x, this->y + b.y};
    }
    Point operator - (const Point& b) {
        return {this->x - b.x, this->y - b.y};
    }
};

struct Segment {
    Point a;
    Point b;
    int id;
};

T cross(Point a, Point b)
{
    return a.x * b.y - a.y * b.x;
}

T dot(Point a, Point b)
{
    return a.x * b.x + a.y * b.y;
}

T orient(Point a, Point b, Point c)
{
    return cross(b - a, c - a);
}

bool intersect_proper(Segment s1, Segment s2)
{
    bool isgood = orient(s1.a, s1.b, s2.a) * orient(s1.a, s1.b, s2.b) < 0;
    isgood = isgood && orient(s2.a, s2.b, s1.a) * orient(s2.a, s2.b, s1.b);

    return isgood;
}

bool inDisk(Segment a, Point p)
{
    return dot(p - a.a, p - a.b) <= 0;
}

bool inside(Segment a, Point p)
{
    return inDisk && orient(a.a, a.b, p) == 0;
}

const long long VAL = 2000000000;
const Segment LOW = {{-VAL, -VAL}, {-VAL, -VAL}};
const Segment HIGH = {{VAL, VAL}, {VAL, VAL}};
int n;
vector<Point> events;
vector<Segment> all;
vector<int> intersect_cnt;
set<Segment> active;
int ans = -1;

bool intersect(Segment s1, Segment s2)
{
    bool isgood=false;
    if (intersect_proper(s1, s2))
        isgood = true;

    if (inside(s1, s2.a) || inside(s1, s2.b) || inside(s2, s1.b))
        isgood = true;

    if (isgood) {
        intersect_cnt[s1.id]++;
        if (intersect_cnt[s1.id] == 2)
            ans = s1.id;
        intersect_cnt[s2.id]++;
        if (intersect_cnt[s2.id] == 2)
            ans = s2.id;
    }
    return isgood;
}

bool operator < (const Point& a, const Point& b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool operator < (const Segment& a, const Segment& b)
{
    if (a.a.y == b.a.y) {
        if (a.b.y == b.b.y) {
            return a.a.x < b.a.x;
        }
        return a.b.y < b.b.y;
    }

    return a.a.y < b.a.y;
}

int main(void)
{
    freopen("cowjump.in", "r", stdin);
    freopen("cowjump.out", "w", stdout);

    scanf("%d", &n);
    intersect_cnt.resize(n);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        Point p1 = {x1, y1, i};
        Point p2 = {x2, y2, i};
        if (p2 < p1)
            swap(p1, p2);
        all.push_back({p1, p2, i});
        events.push_back(p1);
        events.push_back(p2);
    }
    sort(events.begin(), events.end());

    for (auto e : events) {
        if (active.find(all[e.id]) != active.end()) {
            Segment s1 = LOW;
            Segment s2 = HIGH;
            auto prv = active.lower_bound(all[e.id]);
            if (prv != active.begin()) {
                prv--;
                s1 = *prv;
            }
            prv = active.upper_bound(all[e.id]);
            if (prv != active.end())
                s2 = *prv;

            intersect(s1, s2);
            active.erase(all[e.id]);
        }
        else {
            Segment s1 = LOW;
            Segment s2 = HIGH;
            auto prv = active.lower_bound(all[e.id]);
            if (prv != active.begin()) {
                prv--;
                s1 = *prv;
                intersect(s1, all[e.id]);
            }
            prv = active.upper_bound(all[e.id]);
            if (prv != active.end()) {
                s2 = *prv;
                intersect(s2, all[e.id]);
            }

            active.insert(all[e.id]);
        }

        if (ans != -1)
            break;
    }

    printf("%d\n", ans + 1);
    return 0;
}