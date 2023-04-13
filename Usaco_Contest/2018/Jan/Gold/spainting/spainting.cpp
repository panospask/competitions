#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000000
#define MAXM 1000000
#define MOD ((int)1e9 + 7)

using namespace std;

int n, m, k;

/* Key observation: Only one continous segment needs to have length k, all other places
    of the array can have whatever colour we want */

// dp[i][j]: All possible combos up to i
// j being 0 if we have not placed the semgent of length k and 1 otherwise
long long int dp[MAXN + 2][2];

long long int calc_dp(int i, int j)
{
    if (i < 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (j == 0) {
        dp[i][j] = calc_dp(i - 1, j) * m % MOD; // m new possibilities for the new slot
    }
    else {
        if (i > k) {
            dp[i][j] = calc_dp(i - 1, j) * m % MOD;
            dp[i][j] += calc_dp(i - k, 0) * m % MOD;

            dp[i][j] -= (calc_dp(i - k, 0) - calc_dp(i - k, 1)) + calc_dp(i - k, 1) * m % MOD;

            // Careful not to doublecount the segments of length k(there will be m in total)
        }
        else if (i == k) {
            dp[i][j] = m;
        }
        else 
            dp[i][j] = 0;
    }

    dp[i][j] = (dp[i][j] + MOD) % MOD;

    return dp[i][j];
}


int main(void)
{
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &k);
    
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 1; // The only possibility is nothing
    dp[0][1] = 0;
    long long int ans = calc_dp(n, 1);
    if (k == 1)
        ans = calc_dp(n, 0);

    printf("%lld\n", ans);
    return 0;
}