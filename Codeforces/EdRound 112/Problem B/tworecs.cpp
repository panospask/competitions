#include <bits/stdc++.h>

using namespace std;

struct rect {
    int x1, x2, y1, y2;

    void read(void) {
        cin >> x1 >> y1 >> x2 >> y2;
    }
    int area(void) {
        return (x2 - x1) * (y2 - y1);
    }
};
typedef struct rect Rect;

Rect firstrec;
int boxw, boxh;
int recw, rech;
int t;

int main(void)
{
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d", &boxw, &boxh);
        firstrec.read();
        scanf("%d %d", &recw, &rech);

        int minmove = INT_MAX;
        if (recw + firstrec.x2 - firstrec.x1 <= boxw) {
            // Explore moving box left or right

            minmove = min(minmove, max(0, recw - firstrec.x1));
            minmove = min(minmove, max(0, recw - boxw + firstrec.x2));
        }
        if (rech + firstrec.y2 - firstrec.y1 <= boxh) {
            // Explore moving box up or down

            minmove = min(minmove, max(0, rech - firstrec.y1));
            minmove = min(minmove, max(0, rech - boxh + firstrec.y2));
        }

        if (minmove == INT_MAX)
            minmove = -1;
        printf("%d\n", minmove);
    }
}