#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<vector<ll>> dp;
vector<ll> pref;
vector<int> a;

ll sum(int l, int r) {
    ll ans = pref[r];
    if (l)
        ans -= pref[l - 1];

    return ans;
}

int main(void)
{
    scanf("%d", &n);

    a.resize(n);
    pref.resize(n);
    dp.resize(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pref[i] = i ? pref[i - 1] + a[i] : a[i];
    }

    for (int len = 1; len <= n; len++) {
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;

            if (l == r) {
                dp[l][r] = a[l];
                continue;
            }

            dp[l][r] = LLONG_MIN;
            dp[l][r] = max(dp[l][r], a[l] + sum(l + 1, r) - dp[l + 1][r]);
            dp[l][r] = max(dp[l][r], a[r] + sum(l, r - 1) - dp[l][r - 1]);
        }
    }

    printf("%lld\n", dp[0][n - 1]);

    return 0;
}