#include <bits/stdc++.h>
#define MAXN 500
#define MOD ((int)1e9 + 7)

using namespace std;

int n;
// dp[l][r]: The total number of ways to completely delete the string [l...r)
long long int dp[MAXN + 2][MAXN + 2];
string s;

long long calc_dp(int l, int r)
{
    if (l > r) 
        return 1;
    else if (l == r)
        return 0;

    if (dp[l][r] != -1)
        return dp[l][r];

    long long v = 0;
    for (int i = l; i < r; i++) {
        long long add = (calc_dp(l, i) * calc_dp(i+1, r)) %  MOD;
        v = (v + add) % MOD;
    }

    if (s[l] == s[r])
        v += calc_dp(l + 1, r - 1);
    
    v %= MOD;
    dp[l][r] = v;

    return dp[l][r];
}

int main(void)
{
    cin >> s;
    n = s.size();

    memset(dp, -1, sizeof(dp));

    long long ans = calc_dp(0, n-1);

    printf("%lld\n", ans);
    return 0;
}