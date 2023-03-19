#include <bits/stdc++.h>
#define MAXN 1000000
#define MOD ((int)(1e9) + 7)

using namespace std;

typedef long long int ll;

int n;

ll fact[MAXN + 2];

ll calc_power(ll b, ll p, ll mod)
{
    ll x = 1;
    b %= mod;

    while (p > 0) {
        if (p % 2)
            x = x * b % mod;
        
        b = b * b % mod;
        p /= 2;
    }

    return x;
}

void precalculate_factorials(void)
{
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;
}

long long int find_inv(ll a, ll mod)
{
    return calc_power(a, mod - 2, mod);
}

int main(void)
{
    scanf("%d", &n);

    precalculate_factorials();

    int choose_from, choose_size;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &choose_from, &choose_size);

        ll divisor = (fact[choose_size] * fact[choose_from - choose_size]) % MOD;
        ll inv_div = find_inv(divisor, MOD);

        ll ans = fact[choose_from] * inv_div % MOD;

        printf("%lld\n", ans);
    }

    return 0;
}