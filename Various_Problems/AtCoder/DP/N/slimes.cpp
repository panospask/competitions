#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N;
vector<int> a;
vector<ll> pref;

// dp[l][r]: The most optimal way to merge the subsegment [l..r]
vector<vector<ll>> dp;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    pref.resize(N + 1);
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    pref[0] = 0;
    for (int i = 1; i <= N; i++) {
        pref[i] = pref[i - 1] + a[i - 1];
    }

    dp.resize(N, vector<ll>(N));
    for (int len = 1; len <= N; len++)
        for (int l = 0; l <= N - len; l++) {
            int r = l + len - 1;

            if (l == r) {
                dp[l][r] = 0;
                continue;
            }

            dp[l][r] = INF;
            for (int i = l; i < r; i++) {
                // Merge [i..l] and [i+1..r] first
                dp[l][r] = min(dp[l][r], dp[l][i] + dp[i + 1][r]);
            }
            // Merge together the optimal configuration
            dp[l][r] += pref[r + 1] - pref[l];
        }

    printf("%lld\n", dp[0][N - 1]);

    return 0;
}