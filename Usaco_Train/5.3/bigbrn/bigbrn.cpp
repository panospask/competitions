/*
ID: panos.p1
LANG: C++11
TASK: bigbrn
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
// #define DEBUG 

using namespace std;

typedef pair<int, int> ii;

int n, t;
map<ii, bool> hastree;
ii maxdp = mp(0,0);

int dp[2][MAXN];


int main(void)
{
    freopen("bigbrn.in", "r", stdin);
    freopen("bigbrn.out", "w", stdout);

    #ifdef DEBUG
        FILE* mazeprnt;
        mazeprnt = fopen("analysis.out", "w");
    #endif

    scanf("%d %d", &n, &t);
    
    for (int x = 0; x < t; x++) {
        int i, j;
        scanf("%d %d", &i, &j);
        hastree[mp(i-1, j-1)] = true;
    }

    int ans = 0;
    for (int j = 0; j < n; j++) {
        dp[0][j] = (hastree.count(mp(n - 1, j)) >= 1 ? 0 : 1);
        ans = max(ans, dp[0][j]);
    }

    for (int i = n - 2; i >= 0; i--) {
        // dp[1] is the current row
        // dp[0] is the previous row

        dp[1][n-1] = (hastree.count(mp(i, n - 1)) >= 1 ? 0 : 1);
        ans = max(ans, dp[1][n-1]);

        for (int j = n - 2; j >= 0; j--) {
            if (hastree.count(mp(i, j)) == 1)
                dp[1][j] = 0;
            else {
                dp[1][j] = min(dp[1][j+1], min(dp[0][j], dp[0][j+1])) + 1;
            }

            ans = max(ans, dp[1][j]);
            if (ans == dp[1][j])
                maxdp = mp(i, j);
        }

        for (int j = n - 1; j >= 0; j--)
            dp[0][j] = dp[1][j];
    }


    #ifdef DEBUG
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (hastree.count(mp(i, j)) >= 1)
                    fprintf(mazeprnt, "#");
                else {
                    fprintf(mazeprnt, ".");
                }
            }
            fprintf(mazeprnt, "\n");
        }
            fprintf(mazeprnt, "%d %d\n", maxdp.first, maxdp.second);
            fprintf(mazeprnt, "%d\n", (int) hastree.size());

    #endif

    printf("%d\n", ans);
    return 0;
}