#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int LETTER = 26;
const int MOD = (int)1e9 + 7;

int k;
int n;
string s;

vector<ll> fact;
vector<ll> inv;

ll calc_inv(ll a)
{
    int b = MOD - 2;

    ll c = 1;

    while (b) {
        if (b & 1)
            c = c * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

void factorials(void)
{
    fact.resize(n + k + 1);
    inv.resize(n + k + 1);

    fact[0] = 1;
    for (int i = 1; i <= n + k; i++)
        fact[i] = fact[i - 1] * i % MOD;

    inv[n + k] = calc_inv(fact[n + k]);
    for (int i = n + k - 1; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}

ll choose(int a, int b)
{
    if (a < b)
        return 0;

    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
}

int main(void)
{
    cin >> k >> s;
    n = s.size();

    factorials();

    // All possible strings of length (n + k)
    ll ans = 1;
    for (int i = 0; i < n + k; i++)
        ans = ans * LETTER % MOD;

    // Remove the strings that do not contain m
    ll curpow = 1;
    for (int i = 0; i < k + 1; i++)
        curpow = curpow * (LETTER - 1) % MOD;

    for (int pref = n - 1; pref >= 0; pref--) {
        ans -= choose(n + k, pref) * curpow;
        ans = (ans % MOD + MOD) % MOD;

        curpow = curpow * (LETTER - 1) % MOD;
    }

    printf("%lld\n", ans);
}