#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100
#define MAXH 1000
#define MOD ((int)1e9 + 7)

using namespace std;

int n;

// dp[i][j]: The total of i-tuples that can reach a hunger level of j by some feed combo
long long int dp[MAXN + 2][MAXH + 2];
long long int pref[MAXN + 2][MAXH + 2];

int hunger[MAXN + 2];

long long check_zero(int shift)
{
    memset(dp, 0, sizeof(dp));
    memset(pref, 0, sizeof(pref));

    dp[0][0] = 1;
    for (int i = 0; i <= MAXH; i++)
        pref[0][i] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= hunger[i] - shift; j++) {
            dp[i][j] = pref[i-1][(hunger[i] - shift) -j];
            pref[i][j] = dp[i][j];
        }
        for (int j = 1; j <= MAXH; j++) {
            pref[i][j] += pref[i][j-1];
            pref[i][j] %= MOD;
        }
    }

    return dp[n][0];
}

int main(void)
{
    // freopen("drought.in", "r", stdin);
    // freopen("drought.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &hunger[i]);
    }

    long long ans = 0;
    if (n % 2) {
        for (int i = 0; i <= MAXH; i++) {
            ans += check_zero(i);
            ans %= MOD;
        }
    }
    else 
        ans = check_zero(0);
    
    printf("%lld\n", ans);
    return 0;
}