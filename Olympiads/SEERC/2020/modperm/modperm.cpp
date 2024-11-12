#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N;

// dp[i]: Number of ways to split the numbers from N to i into two arcs.
// NOTE: x goes into arc #1 and x + 1 goes into arc #2
vector<ll> dp;

void add(ll& a, ll b)
{
    a += b;
    if (a >= MOD) {
        a -= MOD;
    }
}

int main(void)
{
    scanf("%d", &N);

    dp.resize(N + 1);
    dp[N] = 1;
    dp[N - 1] = 1;

    for (int i = N - 2; i > 0; i--) {
        for (int j = i + 2; j <= N; j++) {
            if (j % i > 2) {
                j = (j / i + 1) * i;
            }
            if (j > N) {
                break;
            }

            add(dp[i], dp[j - 1]);
        }
    }

    ll ans = (dp[1] * 2 * N) % MOD;

    printf("%lld\n", ans);

    return 0;
}