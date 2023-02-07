#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXCOORD 1000

using namespace std;

int n, k;
int mod_by[MAXCOORD + 10][MAXCOORD + 10];
int vertmod[MAXCOORD + 10][MAXCOORD + 10];


int main(void)
{
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);

    scanf("%d %d", &n, &k);
    int x1, y1, x2, y2;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        mod_by[x1][y1]++;
        mod_by[x1][y2]--;
        mod_by[x2][y1]--;
        mod_by[x2][y2]++;        
    }

    int ans = 0;
    for (int i = 0; i <= MAXCOORD; i++)
        for (int j = 0; j <= MAXCOORD; j++) {
            if (i > 0) mod_by[i][j] += mod_by[i - 1][j];
            if (j > 0) mod_by[i][j] += mod_by[i][j-1];
            if (i > 0 && j > 0) mod_by[i][j] -= mod_by[i-1][j-1];

            if (mod_by[i][j] == k)
                ans++;
        }

    printf("%d\n", ans);
    return 0;
}