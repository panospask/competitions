#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N, K;
ll ans;
vector<ll> fact, inv;

ll calc_power(ll b, ll p)
{
    ll x = 1;
    b %= MOD;

    while (p > 0) {
        if (p % 2)
            x = x * b % MOD;

        b = b * b % MOD;
        p /= 2;
    }

    return x;
}

ll find_inv(ll a)
{
    return calc_power(a, MOD - 2);
}

void precalculate_factorials(void)
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
        fact[i] = fact[i-1] * i % MOD;

    inv[N] = find_inv(fact[N]);
    for (int i = N - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

ll choose(int a, int b)
{
    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
}

ll recurse(int i, int rem)
{
    if (rem < 0) {
        return 0;
    }
    if (i == N) {
        return 1;
    }

    ll res = 0;
    for (int j = i + 1; j <= N; i++) {
        if (j - i == 2 && i != 0 && j != N) {
            continue;
        }
        res += recurse(j, rem - 1);
        res %= MOD;
    }

    return
}

int main(void)
{
    scanf("%d %d", &N, &K);

    fact.resize(N + 1);
    inv.resize(N + 1);

    precalculate_factorials();

    ans = 1;
    for (int i = 0; i < N - 1; i++) {
        ans = ans * 2 % MOD;
    }

    ans -= recurse(0, K);
    ans = (ans % MOD + MOD) % MOD;
    printf("%lld\n", ans);

    return 0;
}