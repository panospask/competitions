#include <bits/stdc++.h>
#define MAXN 100
#define MAXM 100

using namespace std;

typedef pair<int, int> ii;

int n, m;
int maxans = 0;

ii roadsegs[MAXN];
ii travelsegs[MAXM];

int main(void)
{
    freopen("speeding.in", "r", stdin);
    freopen("speeding.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &roadsegs[i].first, &roadsegs[i].second);
    for (int i = 0; i < m; i++)
        scanf("%d %d", &travelsegs[i].first, &travelsegs[i].second);

    int curi = 0, curj = 0;
    ii cur_road = roadsegs[0];
    ii cur_travel = travelsegs[0];
    while (curi < n && curj < m) {
        maxans = max(maxans, cur_travel.second - cur_road.second);

        int remove = min(cur_road.first, cur_travel.first);
        cur_road.first -= remove;
        cur_travel.first -= remove;
        if (cur_road.first == 0) {
            cur_road = roadsegs[++curi];
        }
        if (cur_travel.first == 0) {
            cur_travel = travelsegs[++curj];
        }
    }

    printf("%d\n", maxans);
    return 0;
}