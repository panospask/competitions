#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int fj_gest[MAXN + 5];
int wins[3][MAXN + 5];
int n;
int ans = 0;

int main(void)
{
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    scanf("%d", &n);
    char c;
    for (int j = 0; j < 3; j++)
        wins[j][0] = 0;
    for (int i = 1; i <= n; i++) {
        getchar();
        c = getchar();
        for (int j = 0; j < 3; j++)
            wins[j][i] = wins[j][i - 1];

        if (c == 'H') {
            fj_gest[i] = 0;
        }
        else if (c == 'S') {
            fj_gest[i] = 1;
        }
        else {
            fj_gest[i] = 2;
        }

    
        wins[(fj_gest[i] + 2) % 3][i]++;
    }

    int curwins;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            curwins = wins[j][i];
            for (int k = 0; k < 3; k++) {
                curwins += wins[k][n] - wins[k][i];
                if (curwins > ans)
                    ans = curwins;
                curwins -= wins[k][n] - wins[k][i];
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}