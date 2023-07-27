#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> a;
vector<ll> pref;

// dp[l][r]: Maximum score if the deque is reduced to L..R for the player that plays first at the time
vector<vector<ll>> dp;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    dp.resize(N, vector<ll>(N));
    pref.resize(N + 1);

    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        pref[i + 1] = pref[i] + a[i];
    }

    for (int len = 1; len <= N; len++)
        for (int l = 0; l <= N - len; l++) {
            int r = l + len - 1;

            if (l == r) {
                dp[l][r] = a[l];
                continue;
            }

            dp[l][r] = 0;
            ll maxsum = pref[r + 1] - pref[l];
            dp[l][r] = max(dp[l][r], maxsum - dp[l][r - 1]);
            dp[l][r] = max(dp[l][r], maxsum - dp[l + 1][r]);
        }

    ll ans = 2 * dp[0][N - 1] - pref[N];
    printf("%lld\n", ans);

    return 0;
}