#include <bits/stdc++.h>
#define MAXN 1000000
#define MOD 1000000007

using namespace std;

typedef long long int ll;

ll fact[2 * MAXN + 1];

ll calc_power(ll a, ll b, ll mod)
{
    ll x = 1;
    a %= mod;

    while (b > 0) {
        if (b % 2 == 1) 
            x = x * a % mod;

        a = a * a % mod;
        b /= 2;
    }

    return x;
}


void precalc_fact(void)
{
    fact[0] = 1;
    for (int i = 1; i < 2 * MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;
}

ll find_inv(ll a, ll mod)
{
    return calc_power(a, mod - 2, mod);
}

int n, m;

int main(void)
{
    scanf("%d %d", &n, &m);
    precalc_fact();
    
    ll inv_div = find_inv((fact[m] * fact[n - 1]) % MOD, MOD);

    ll ans = fact[n - 1 + m ] * inv_div % MOD;

    printf("%lld\n", ans);
    return 0;
}