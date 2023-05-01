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

T sign(T a)
{
    return a == 0 ? 0 : (a < 0 ? -1 : 1);
}

const long long VAL = 1e9 + 2;
const Segment LOW = {{-VAL, -VAL}, {-VAL, -VAL + 1}};
const Segment HIGH = {{VAL, VAL}, {VAL, VAL + 1}};

int n;
double x;
vector<Point> events;
vector<Segment> all;
vector<int> intersect_cnt;
set<Segment> active;
int ans = -1;
pair<int, int> check;

double eval(Segment s)
{
    if (s.a.x == s.b.x)
        return s.a.y;

    return s.a.y + (s.b.y - s.a.y) * (x - s.a.x) / (s.b.x - s.a.x);
}

bool operator < (const Point a, const Point b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool operator == (const Point a, const Point b)
{
    return (a.x == b.x) && (a.y == b.y);
}
bool operator <= (const Point a, const Point b)
{
    return a < b || a == b;
}

bool operator < (const Segment& a, const Segment& b)
{
    if (a.id == b.id)
        return false;

    return eval(a) < eval(b);
}

bool intersect(Segment s1, Segment s2)
{

    int oa = sign(orient(s2.a, s2.b, s1.a));
    int ob = sign(orient(s2.a, s2.b, s1.b));
    int oc = sign(orient(s1.a, s1.b, s2.a));
    int od = sign(orient(s1.a, s1.b, s2.b));

    if (oa * ob < 0 && oc * od < 0)
        return true;
    if (oa * ob <= 0 && oc * od < 0)
        return true;
    if (oa * ob < 0 && oc * od <= 0)
        return true;

    if (oa * ob == 0 && oc * od == 0) {
        Point m1 = min(s1.a, s1.b);
        Point m2 = min(s2.a, s2.b);
        Point M1 = max(s1.a, s1.b);
        Point M2 = max(s2.a, s2.b);

        if (max(m1, m2) <= min(M1, M2))
            return true;
    }

    return false;
}

int inter(Segment a)
{
    int c = 0;
    for (int i = 0; i < all.size(); i++) {
        if (i == a.id)
            continue;

        c += intersect(all[i], a);
    }

    return c;
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
        x = e.x;
        Segment s = all[e.id];
        if (active.find(s) != active.end()) {
            // Remove it
            Segment l = LOW;
            Segment r = HIGH;

            auto prv = active.find(s);
            if (prv != active.begin()) {
                prv--;
                l = *prv;
            }
            auto nxt = active.find(s);
            nxt++;
            if (nxt != active.end()) {
                r = *nxt;
            }

            if (intersect(l ,r)) {
                check = mp(l.id, r.id);
                break;
            }

            active.erase(s);
        }
        else {
            //Add it
            Segment l = LOW;
            Segment r = HIGH;

            active.insert(s);

            auto prv = active.find(s);
            if (prv != active.begin()) {
                prv--;
                l = *prv;
            }
            auto nxt = active.find(s);
            nxt++;
            if (nxt != active.end()) {
                r = *nxt;
            }

            if (intersect(l ,s)) {
                check = make_pair(l.id, s.id);
                break;
            }
            if (intersect(r ,s)) {
                check = mp(r.id, s.id);
                break;
            }

            active.insert(s);
        }
    }

    // Check the checks
    int c1 = inter(all[check.first]);
    int c2 = inter(all[check.second]);

    if (c1 == 1 && c2 == 1)
        ans = min(check.first, check.second);
    else if (c1 > 1)
        ans = check.first;
    else
        ans = check.second;

    printf("%d\n", ans + 1);
    return 0;
}