#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int INV2 = 5e8 + 4;

ll N;
ll ans = 0;

// Needs MOD many times to avoid overflow

int main(void)
{
    scanf("%lld", &N);

    ll CUT = 1;
    while (CUT * CUT <= N) {
        CUT++;
    }

    for (ll i = 1; i * i <= N; i++) {
        // Calculate how many times i appears as a divisor

        ll times = N / i;
        ans += (i % MOD) * (times % MOD) % MOD;
        ans %= MOD;

        // Also add the pair-divisors when they are bigger than or equal to CUT
        ans += ((times - CUT) % MOD) * ((times - CUT + 1) % MOD) % MOD * INV2 % MOD;
        ans %= MOD;
        ans += ((times - (CUT - 1)) % MOD) * (CUT % MOD);
        ans %= MOD;
    }

    printf("%lld\n", ans);

    return 0;
}