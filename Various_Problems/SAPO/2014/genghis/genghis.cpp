#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;
vector<int> x;
vector<vector<ll>> dp;

int main(void)
{
    scanf("%d %d", &n, &k);

    x.resize(k + 2);

    x[0] = 0;
    for (int i = 1; i <= k; i++)
        scanf("%d", &x[i]);
    x[k + 1] = n + 1;
    sort(x.begin(), x.end());

    k += 2;

    dp.assign(k, vector<ll>(k, LONG_LONG_MAX));

    for (int len = 1; len <= k; len++)
        for (int l = 0; l <= k - len; l++) {
            int r = l + len - 1;

            if (l == r) {
                dp[l][r] = 0;

                continue;
            }
            else if (l == r - 1) {
                dp[l][r] = 0;

                continue;
            }

            for (int i = l + 1; i < r; i++) {
                ll ans = 0;
                if (i - 1 >= l)
                    ans += dp[l][i];
                if (i + 1 <= r)
                    ans += dp[i][r];

                // All horses in the range (x[l], x[r]) will also take 1 additional operation
                // to climb down from i

                ans += ((x[r] - 1) - x[l]);

                dp[l][r] = min(dp[l][r], ans);
            }
        }

    printf("%lld\n", dp[0][k - 1]);
}