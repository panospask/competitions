#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = (int)1e9 + 7;

ll calc_pow(ll a, int b)
{
    ll c = 1;

    while (b) {
        if (b % 2)
            c = c * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

ll calc_inv(int a)
{
    return calc_pow(a, MOD - 2);
}

int n;
ll ans = 0;
vector<ll> fact;

ll choose(int a, int b)
{
    if (a < b)
        return 0;

    ll nom = fact[a];
    ll den = calc_inv(fact[b]) * calc_inv(fact[a - b]) % MOD;

    return (nom * den) % MOD;
}

int main(void)
{
    scanf("%d", &n);

    fact.resize(2 * n + 2);

    ll cur_states = 1;
    fact[0] = 1;
    for (int i = 0; i <= 2 * n; i++) {
        ans += cur_states;
        ans %= MOD;

        ll s = 2 * choose(i, n) % MOD;
        cur_states = ((2 * cur_states) - s) % MOD;
        cur_states = (cur_states + MOD) % MOD;
        fact[i + 1] = fact[i] * (i + 1) % MOD;
    }

    printf("%lld\n", ans);
    return 0;
}