#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = (int)1e9 + 7;

vector<ll> must_have;
vector<ll> dp;

void solve(int N)
{
    must_have.resize(N + 1);
    dp.resize(N + 1);

    must_have[0] = dp[0] = 1;
    ll tot = 1;
    ll must_tot = 1;
    for (int i = 1; i <= N; i++) {
        must_have[i] = tot;

        dp[i] = (4 * dp[i - 1] - 3 * must_have[i - 1] + must_have[i]) % MOD;
        if (dp[i] < 0)
            dp[i] += MOD;

        tot = (tot + dp[i]) % MOD;
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    solve(1000000);
    while (t--) {
        int i;
        scanf("%d", &i);
        printf("%lld\n", dp[i]);
    }

    return 0;
}