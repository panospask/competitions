#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, W;
vector<int> a;
vector<int> v;

vector<ll> prev_dp;
vector<ll> dp;

int main(void)
{
    scanf("%d %d", &N, &W);

    a.resize(N);
    v.resize(N);
    prev_dp.assign(W + 1, 0);
    dp.resize(W + 1);

    for (int i = 0; i < N; i++)
        scanf("%d %d", &a[i], &v[i]);

    for (int i = 0; i < N; i++) {
        dp[0] = 0;
        for (int j = 0; j < W; j++) {
            dp[j] = max(dp[j], prev_dp[j]);
            dp[j + 1] = max(dp[j], dp[j + 1]);

            if (j + a[i] <= W)
                dp[j + a[i]] = max(dp[j + a[i]], prev_dp[j] + v[i]);
        }

        prev_dp = dp;
        dp.assign(W + 1, 0);
    }

    printf("%lld\n", prev_dp[W]);

    return 0;
}