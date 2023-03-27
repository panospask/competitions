#include <bits/stdc++.h>
#define MAXN 100000
#define MAXM 100
#define mp make_pair
#define MOD ((int)1e9 + 7)

using namespace std;

typedef pair<int, int> ii;

int n, m;
long long int dp[MAXN + 2][MAXM + 2];
int a[MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (a[0] == 0) {
        for (int v = 1; v <= m; v++)
            dp[0][v] = 1;
    }
    else 
        dp[0][a[0]] = 1;

    for (int i = 0; i < n - 1; i++) {
        if (a[i] == 0) {
            for (int v = 1; v <= m; v++) {
                if (dp[i][v] == 0) continue;


                if (v != 1)
                    dp[i+1][v-1] = (dp[i+1][v-1] + dp[i][v]) % MOD;
                
                dp[i+1][v] = (dp[i+1][v] + dp[i][v]) % MOD;

                if (v != m)
                    dp[i+1][v+1] = (dp[i+1][v+1] + dp[i][v]) % MOD;
            }
        }
        else {
            int val = a[i];

            if (val != 1)
                 dp[i+1][val-1] = (dp[i+1][val-1] + dp[i][val]) % MOD;

            dp[i+1][val] = (dp[i+1][val] + dp[i][val]) % MOD;

            if (val != m)
                dp[i+1][val+1] = (dp[i+1][val+1] + dp[i][val]) % MOD;
        }
    }

    long long int ans = 0;
    if (a[n-1]) {
        ans = dp[n-1][a[n-1]];
    }
    else {
        for (int v = 1; v <= m; v++)
            ans = (ans + dp[n-1][v]) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}