#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
vector<int> primes;
vector<bool> isprime;

/* dp[j][i]: Sum of all the numbers K such that the sum of their prime
 * decomposition is i (using only the first j primes)
 */
vector<vector<ll>> dp;

int main(void)
{
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);

    scanf("%d %d", &N, &M);

    isprime.assign(N + 1, true);

    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            primes.push_back(i);
        }

        for (auto p : primes) {
            if (p * i > N) {
                break;
            }
            isprime[p * i] = false;

            if (i % p == 0) {
                break;
            }
        }
    }

    dp.assign(primes.size() + 1, vector<ll>(N + 1, 0));

    dp[0][0] = 1;
    for (int j = 0; j < primes.size(); j++) {
        int primepow = primes[j];
        while (primepow <= N) {
            for (int s = N - primepow; s >= 0; s--) {
                dp[j + 1][s + primepow] += dp[j][s] * primepow % M;
                dp[j + 1][s + primepow] %= M;
            }

            primepow *= primes[j];
        }

        for (int s = 0; s <= N; s++) {
            dp[j + 1][s] += dp[j][s];
            dp[j + 1][s] %= M;
        }
    }

    ll ans = 0;
    for (int i = 0; i <= N; i++) {
        ans += dp[primes.size()][i];
        ans %= M;
    }

    printf("%lld\n", ans);
    return 0;
}