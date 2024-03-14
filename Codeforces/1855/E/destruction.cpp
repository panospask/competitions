#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = (int)1e9 + 7;
const int INV2 = 5e8 + 4;

int N, M;
vector<vector<ll>> dp;

int main(void)
{
    scanf("%d %d", &N, &M);

    dp.resize(M + 1, vector<ll>(M + 1));

    for (int i = M; i >= 0; i--)
        for (int j = M; j > i; j--) {
            if (j != M)
                dp[i][j] = INV2 * (dp[i + 1][j] + 1 + dp[i][j + 1]) % MOD;
            else
                dp[i][j] = dp[i + 1][j] + 1;
        }

    ll ans = 0;
    int prv = -1;
    for (int i = 0; i < N; i++) {
        int num;
        scanf("%d", &num);
        num--;

        if (prv != -1)
            ans += dp[prv][num];
        prv = num;
    }
    ans += dp[prv][M];

    printf("%lld\n", ans % MOD);

    return 0;
}