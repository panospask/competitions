#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = (int)1e9 + 7;

const int LETTER = 26;

ll k, n;
string s;

vector<ll> fact;
vector<ll> inv;

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

ll calc_inv(ll a)
{
    return calc_pow(a, MOD - 2);
}

ll choose(int a, int b)
{
    if (a < b)
        return 0;

    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
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

int main(void)
{
    cin >> k >> s;
    n = s.size();

    factorials();
    ll ans = 0;
    for (int pos = n - 1; pos < n + k; pos++) {
        // What if s.back() ends up in this position

        int add_front = (pos - n + 1);
        int add_back = k - add_front;

        ll possible_front = choose(pos, add_front) * calc_pow(LETTER - 1, add_front) % MOD;
        ll possible_back = calc_pow(LETTER, add_back);

        ans += possible_front * possible_back % MOD;
        ans %= MOD;
    }

    printf("%lld\n", ans);
}