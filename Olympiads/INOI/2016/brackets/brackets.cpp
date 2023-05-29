#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<vector<int>> dp;

vector<int> b;
vector<int> v;

bool match(int i, int j)
{
    return i == j - k;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    v.resize(n);
    b.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    dp.assign(n, vector<int>(n, -1));
    for (int len = 1; len <= n; len++)
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;

            if (r == l) {
                dp[l][r] = 0;
                continue;
            }

            dp[l][r] = 0;
            for (int i = l; i <= r; i++) {
                if (match(b[l], b[i])) {
                    int res = v[l] + v[i];
                    if (i - 1 >= l + 1)
                        res += dp[l + 1][i - 1];
                    if (i + 1 <= r)
                        res += dp[i + 1][r];

                    dp[l][r] = max(dp[l][r], res);
                }
                int res = dp[l][i];
                if (i + 1 <= r)
                    res += dp[i + 1][r];

                dp[l][r] = max(dp[l][r], res);
            }
        }

    printf("%d\n", dp[0][n-1]);
    return 0;
}