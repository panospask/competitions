#include <bits/stdc++.h>
#define MAXN 21
#define MOD ((int)1e9 + 7)
#define CHECK_BIT(val, pos) (val & (1<<pos))

using namespace std;

// dp[s]: The number of matching of the women in s to the first |s| men
long long int dp[(1<<MAXN)];
int n;

// match[i][j] is true if man[i] matches woman[j], false otherwise
int match[MAXN + 2][MAXN + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &match[i][j]);

    dp[0] = 1; // Only 1 match, match no woman with no man
    for (int s = 0; s < (1<<n); s++) {
        int num = __popcount(s);
        for (int w = 0; w < n; w++) {
            if (CHECK_BIT(s, w) || !match[num][w])
                continue;

            dp[s + (1<<w)] += dp[s];
            dp[s + (1<<w)] %= MOD;
        }
    }

    printf("%lld\n", dp[(1<<n)-1]);
    return 0;
}