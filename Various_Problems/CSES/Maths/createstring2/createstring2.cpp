#include <bits/stdc++.h>
#define MAXN 1000000
#define MOD 1000000007

using namespace std;

typedef long long int ll;

ll fact[MAXN + 3];
ll inv_fact[MAXN + 3];

ll calc_power(ll b, ll p, int mod)
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

void precalc_factorials(void)
{
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i-1] * i % MOD;
}

void precalc_inverses(void)
{
    // Calculate the inverse of the largest factorial

    inv_fact[MAXN] = calc_power(fact[MAXN], MOD - 2, MOD);
    for (int i = MAXN - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
}

string s;
unordered_map<char, int> times;

int main(void)
{
    cin >> s;
    for (int c = 0; c < s.size(); c++)
        times[s[c]]++;

    precalc_factorials();
    precalc_inverses();

    ll ans = fact[(int)s.size()];
    for (auto appear : times) {
        ans = ans * inv_fact[appear.second] % MOD;
    } 

    printf("%lld\n", ans);
    return 0;
}