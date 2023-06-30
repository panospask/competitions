#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = (int)1e9 + 7;
const int MAXN = 10000;

// The problem statement can be interpeted as counting the number of 132-avoiding permutations
int n;
ll ans = 0;
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

void precalc_fact(void)
{
    fact.resize(MAXN + 5);
    inv.resize(MAXN + 5);
    fact[0] = 1;
    for (int i = 1; i < MAXN + 5; i++)
        fact[i] = fact[i - 1] * i % MOD;

    inv[MAXN + 1] = calc_inv(fact[MAXN + 1]);
    for (int i = MAXN; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}

ll choose(int a, int b)
{
    if (a < b)
        return 0;

    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    ll res = (nom * den % MOD);
    return res;
}

int main(void)
{
    int T;
    scanf("%d", &T);

    precalc_fact();

    for (int i = 0; i < T; i++) {
        int N;
        scanf("%d", &N);

        ll ans = choose(2 * N, N) * calc_inv(N + 1) % MOD;
        printf("%lld\n", ans);
    }

    return 0;
}