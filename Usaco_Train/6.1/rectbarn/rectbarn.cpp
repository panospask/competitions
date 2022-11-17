/*
ID: panos.p1
LANG: C++11
TASK: rectbarn
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 3000

using namespace std;

bool broken[MAXN][MAXN];
int height[MAXN], le[MAXN], ri[MAXN];
int r, c, p;

int main(void)
{
    freopen("rectbarn.in", "r", stdin);
    freopen("rectbarn.out", "w", stdout);

    scanf("%d %d %d", &r, &c, &p);

    int i, j;
    for (int x = 0; x < p; x++) {
        scanf("%d %d", &i, &j);
        broken[i-1][j-1] = true;
    }

    int k;
    int ans = 0;
    for (i = 0; i < r; i++) {
        k = 0;
        for (int j = 0; j < c; j++) {
            if (broken[i][j])
                le[j] = height[j] = k = 0;
            else {
                k++;
                if (le[j] == 0)
                    le[j] = k;
                else 
                    le[j] = min(le[j], k);

                height[j]++;
            }
        }
        k = 0;
        for (int j = c - 1; j >= 0; j--) {
            if (broken[i][j])
                ri[j] = k = 0;
            else {
                k++;
                if (ri[j] == 0)
                    ri[j] = k;
                else 
                    ri[j] = min(ri[j], k);
                
                ans = max(ans, height[j] * (ri[j] + le[j] - 1));
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}