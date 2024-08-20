#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, Q, M;
vector<int> A;
vector<vector<ll>> dp;
vector<vector<ll>> val;

int main(void)
{
    scanf("%d %d %d", &N, &Q, &M);

    A.resize(N);
    dp.resize(N, vector<ll>(N, 0));
    val.resize(N, vector<ll>(N, 0));

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int len = 1; len <= N; len++) {
        for (int l = 0; l + len <= N; l++) {
            int r = l + len - 1;

            if (l == r) {
                dp[l][r] = A[l] % M;
                val[l][r] = A[l];
                continue;
            }

            val[l][r] = lcm(val[l + 1][r], A[l]);

            dp[l][r] = val[l][r] % M + dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1];
            dp[l][r] = (dp[l][r] % M + M) % M;
        }
    }

    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;

        printf("%lld\n", dp[l][r] % M);
    }

    return 0;
}