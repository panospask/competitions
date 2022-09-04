/*
ID: panos.p1
LANG: C++11
TASK: picture
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)5000
#define MAXCOORD (int)10e4

using namespace std;

struct HLine {
    int y, x1, x2, start;

    HLine(int a, int b, int c, int d) {
        this->y = a;
        this->x1 = b;
        this->x2 = c;
        this->start = d;
    }
};

struct VLine {
    int x, y1, y2, start;

    VLine(int a, int b, int c, int d) {
        this->x = a;
        this->y1 = b;
        this->y2 = c;
        this->start = d;
    }
};

bool compH(HLine a, HLine b) {
    if (a.y == b.y)
        return a.start < b.start;
    
    return a.y < b.y;
}
bool compV(VLine a, VLine b) {
    if (a.x == b.x)
        return a.start < b.start;
    
    return a.x < b.x;
}

vector<VLine> VLines;
vector<HLine> HLines;
int n;
int ttl_perimeter = 0;
int x_coord_count[MAXCOORD * 2 + 1];
int y_coord_count[MAXCOORD * 2 + 1];

int main(void)
{
    freopen("picture.in", "r", stdin);
    freopen("picture.out", "w", stdout);

    scanf("%d", &n);
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        // Don't deal with negatives
        x1 += MAXCOORD;
        y1 += MAXCOORD;
        x2 += MAXCOORD;
        y2 += MAXCOORD;

        HLines.pb(HLine(y1, x1, x2, 0));
        HLines.pb(HLine(y2, x1, x2, 1));
        VLines.pb(VLine(x1, y1, y2, 0));
        VLines.pb(VLine(x2, y1, y2, 1));
    }
    int add_or_remove;

    sort(HLines.begin(), HLines.end(), compH);
    sort(VLines.begin(), VLines.end(), compV);

    // Iterate through all horizontal lines in increasing y order
    memset(x_coord_count, 0, sizeof(x_coord_count));
    for (auto& ln : HLines) {
        add_or_remove = (ln.start == 0 ? 1 : -1);

        for (int i = ln.x1; i < ln.x2; i++) {
            if (x_coord_count[i] == ln.start) // Entering / Exiting a shape --> must count for perimeter
                ttl_perimeter++;
            x_coord_count[i] += add_or_remove;
        }
    }

    // Iterate through all vertical lines in increasing x order
    memset(y_coord_count, 0, sizeof(y_coord_count));
    for (auto& ln : VLines) {
        add_or_remove = (ln.start == 0 ? 1 : -1);

        for (int i = ln.y1; i < ln.y2; i++) {
            if (y_coord_count[i] == ln.start)
                ttl_perimeter++;
            y_coord_count[i] += add_or_remove;
        }
    }

    printf("%d\n", ttl_perimeter);
    return 0;
}