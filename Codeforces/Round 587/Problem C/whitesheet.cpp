#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct rect {
    int x1, x2, y1, y2;

    void read(void) {
        cin >> x1 >> x2 >> y1 >> y2;
    }
    int area(void) {
        return (x2 - x1) * (y2 - y1);
    }
};
typedef struct rect Rect;

Rect whitesheet, black1, black2;

int intersect_range(ii a, ii b)
{
    return max(0, min(a.second, b.second) - max(a.first, b.first));
}

int intersect_area(Rect a, Rect b)
{
    return intersect_range(mp(a.x1, a.x2), mp(b.x1, b.x2)) * intersect_range(mp(a.y1, a.y2), mp(b.y1, b.y2));
}

int main(void)
{
    whitesheet.read();
    black1.read();
    black2.read();

    int area_rem = whitesheet.area() - intersect_area(whitesheet, black1) - intersect_area(whitesheet, black2) + intersect_area(black1, black2);

    if (area_rem > 0)
        printf("YES\n");
    else    
        printf("NO\n");

    return 0;
}