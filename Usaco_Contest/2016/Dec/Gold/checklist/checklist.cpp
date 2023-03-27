#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXCOWS 1000

using namespace std;

typedef pair<int, int> ii;

//d[i][j]: Minimum energy to visit i holsteins and j guernseys, 0 if it ends at i-th holstein, 1 if it ends at j-th guernsey 
long long int dp[MAXCOWS + 2][MAXCOWS + 2][2];
ii position[MAXCOWS + 2][MAXCOWS + 2];

ii holsteins[MAXCOWS + 2];
ii guernseys[MAXCOWS + 2];
int h, g;

int main(void)
{
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);

    scanf("%d %d", &h, &g);
    for (int i = 1; i <= h; i++)
        scanf("%d %d", &holsteins[i].first, &holsteins[i].second);
    for (int i = 1; i <= g; i++)
        scanf("%d %d", &guernseys[i].first, &guernseys[i].second);

    // Remove the last holstein and add it at the end
    h--;

    for (int i = 0; i <= h; i++)
        for (int j = 0; j <= g; j++)
            dp[i][j][0] = dp[i][j][1] = -1;

    // Starting at the first holstein
    dp[1][0][0] = 0;
    for (int i = 1; i <= h; i++)
        for (int j = 0; j <= g; j++) 
            for (int e = 0; e < 2; e++) {
                if (dp[i][j][e] == -1) continue;

                ii cursquare = (e == 0 ? holsteins[i] : guernseys[j]);

                // Advance to the next holstein
                if (i != h) {
                    ii next = holsteins[i+1];
                    long long int d = (long long int)(cursquare.first - next.first) * (cursquare.first - next.first) + (long long int)(cursquare.second - next.second) * (cursquare.second - next.second);

                    if (dp[i+1][j][0] == -1)
                        dp[i+1][j][0] = dp[i][j][e] + d;
                    else
                        dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j][e] + d);
                }

                // Advance to the next guernsey 
                if (j != g) {
                    ii next = guernseys[j+1];
                    long long int d = (long long int)(cursquare.first - next.first) * (cursquare.first - next.first) + (long long int)(cursquare.second - next.second) * (cursquare.second - next.second);

                     if (dp[i][j+1][1] == -1)
                        dp[i][j+1][1] = dp[i][j][e] + d;
                    else
                        dp[i][j+1][1] = min(dp[i][j+1][1], dp[i][j][e] + d);
                }
            }

    // Now move to the last holstein
    h++;
    long long int ans = 0;
    ii square = holsteins[h];

    h--;
    ii sq1 = holsteins[h];
    long long int d1 = dp[h][g][0] + (long long int)(sq1.first - square.first) * (sq1.first - square.first) + (long long int)(sq1.second - square.second) * (sq1.second - square.second);

    ii sq2 = guernseys[g];
    long long int d2 = dp[h][g][1] + (long long int)(sq2.first - square.first) * (sq2.first - square.first) + (long long int)(sq2.second - square.second) * (sq2.second - square.second); 

    ans = min(d1,d2);

    printf("%lld\n", ans);
    return 0;
}