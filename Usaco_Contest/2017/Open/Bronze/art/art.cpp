#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 10

using namespace std;

typedef pair<int, int> ii;

int canvas[MAXN][MAXN];
int n;

map<int, int> maxx;
map<int, int> maxy;
map<int, int> minx;
map<int, int> miny;
set<int> digfound;
map<int, bool> can_be;

void check_whole_square(ii tl, ii br, int val)
{
    for (int i = tl.second; i <= br.second; i++)
        for (int j = tl.first; j <= br.first; j++)
            if (canvas[i][j] != val)
                can_be[canvas[i][j]] = false;

    return;
}

int main(void)
{
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);

    scanf("%d", &n);
    int sqval;
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) {
            scanf("%1d", &sqval);
            canvas[i][j] = sqval;
            if (sqval != 0) {
                digfound.insert(sqval);
                can_be[sqval] = true;
                if (minx.count(sqval) == 0) {
                    minx[sqval] = j;
                    miny[sqval] = i;
                    maxx[sqval] = j;
                    miny[sqval] = i;
                }
                else {
                    minx[sqval] = min(minx[sqval], j);
                    miny[sqval] = min(miny[sqval], i);
                    maxx[sqval] = max(maxx[sqval], j);
                    maxy[sqval] = max(maxy[sqval], i);
                }
            }
        }

    // Check every formed square for being complete
    int ans = 0;
    for (auto digit : digfound) {
        check_whole_square(mp(minx[digit], miny[digit]), mp(maxx[digit], maxy[digit]), digit);
    }
    for (auto digit : digfound)
        ans += can_be[digit];

    printf("%d\n", ans);
    return 0;
}