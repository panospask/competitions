#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

typedef pair<int, int> ii;

ii cowcords[MAXN];
int n;
int minans = INT_MAX;
set<int> xcoords;
set<int> ycoords;

int find_opt_line(int y)
{
    int opt = INT_MAX;
    int tr = 0;
    int tl = 0;
    int br = 0;
    int bl = 0;
    for (int i = 0; i < n; i++) {
        if (cowcords[i].first > y)
            tr++;
        else 
            br++;
    }

    int prevy = -1;
    int curcow = 0;
    for (auto x : xcoords) {
        if (curcow == n)
            break;
        while (cowcords[curcow].second < x && curcow < n) {
            if (cowcords[curcow].first < y) {
                br--;
                bl++;
            }
            else {
                tr--;
                tl++;
            }
            curcow++;
        }

        opt = min(opt, max(max(tr, tl), max(br, bl)));
    }

    return opt;
}

int main(void)
{
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cowcords[i].first, &cowcords[i].second);
        xcoords.insert(cowcords[i].first + 1);
        xcoords.insert(cowcords[i].first - 1);
        ycoords.insert(cowcords[i].second + 1);
        ycoords.insert(cowcords[i].second - 1);
    }

    sort (cowcords, cowcords + n);

    for (auto y : ycoords)
        minans = min(minans, find_opt_line(y));

    printf("%d\n", minans);
    return 0;
}