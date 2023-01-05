#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct rect {
    int x1, x2, y1, y2;

    void read(void) {
        cin >> this->x1 >> this->y1 >> this->x2 >> this->y2;
    }
    long long int area(void) {
        return (long long int)(x2 - x1) * (y2 - y1);
    }
};
typedef struct rect Rect;

Rect whitesheet, black1, black2;

bool intersecting(Rect a, Rect b) 
{
    if (a.x1 >= b.x2 || b.x1 >= a.x2 || a.y1 >= b.y2 || b.y1 >= a.y2) 
        return false;

    return true;
}

bool full_cover(Rect a, Rect b)
{
    if (a.x1 <= b.x1 && a.x2 >= b.x2 && a.y1 <= b.y1 && a.y2 >= b.y2)
        return true;
    
    return false;
}

Rect intersection_of(Rect a, Rect b)
{
    Rect c;
    c.x1 = max(a.x1, b.x1);
    c.y1 = max(a.y1, b.y1);
    c.x2 = min(a.x2, b.x2);
    c.y2 = min(a.y2, b.y2);

    return c;
}

int main(void)
{
    whitesheet.read();
    black1.read();
    black2.read();

    bool intersect1 = intersecting(whitesheet, black1);
    bool intersect2 = intersecting(whitesheet, black2);

    long long int area_rem = whitesheet.area();
    if (intersect1) {
        area_rem -= intersection_of(whitesheet, black1).area();
    }
    if (intersect2) {
        area_rem -= intersection_of(whitesheet, black2).area();
    }
    if (intersect1 && intersect2) {
        if (intersecting(intersection_of(whitesheet, black1), intersection_of(whitesheet, black2)))
            area_rem += intersection_of(intersection_of(whitesheet, black1), intersection_of(whitesheet, black2)).area();
    }


    if (area_rem > 0 && !full_cover(black1, whitesheet) && !full_cover(black2, whitesheet))
        printf("YES\n");
    else    
        printf("NO\n");

    return 0;
}