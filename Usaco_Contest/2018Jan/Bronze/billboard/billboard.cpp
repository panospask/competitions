#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct rect {
    ii bl;
    ii tr;

    int area(void) {
        return (tr.first - bl.first) * (tr.second - bl.second);
    }
    void read(void) {
        cin >> bl.first >> bl.second >> tr.first >> tr.second;
    }
};
typedef struct rect Rect;

Rect billboard, lawnmower;

int inter_size(ii range1, ii range2)
{
    return max(0, min(range1.second, range2.second) - max(range1.first, range2.first));
}

bool intersect(ii range1, ii range2)
{
    if (range1.first <= range2.first && range1.second >= range2.first && range1.second <= range2.second)
        return true;
    if (range1.first >= range2.first && range1.second >= range2.second && range1.first <= range2.second)
        return true;
    return false;
}

int main(void)
{
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);

    lawnmower.read();
    billboard.read();

    int area = lawnmower.area();
    bool cover_x = billboard.bl.first <= lawnmower.bl.first && billboard.tr.first >= lawnmower.tr.first && intersect(mp(billboard.bl.second, billboard.tr.second), mp(lawnmower.bl.second, lawnmower.tr.second));
    bool cover_y = billboard.bl.second <= lawnmower.bl.second && billboard.tr.second >= lawnmower.tr.second && intersect(mp(billboard.bl.first, billboard.tr.first), mp(lawnmower.bl.first, lawnmower.tr.first));

    if (cover_x && cover_y)
        area = 0;
    else if (cover_x) {
        area -= max(0, (lawnmower.tr.first - lawnmower.bl.first) * inter_size(mp(lawnmower.bl.second, lawnmower.tr.second), mp(billboard.bl.second, billboard.tr.second)));
    }
    else if (cover_y) {
        area -= max(0, (lawnmower.tr.second - lawnmower.bl.second) * inter_size(mp(lawnmower.bl.first, lawnmower.tr.first), mp(billboard.bl.first, billboard.tr.first)));
    }

    printf("%d\n", area);
    return 0;
} 