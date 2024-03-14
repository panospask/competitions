#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = ((int)1e9 + 7);

int n, m, v;
vector<int> initial;

ll calc_pow(ll a, int b)
{
    ll c = 1;
    while (b) {
        if (b % 2)
            c = a * c % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

ll calc_inv(ll a)
{
    return calc_pow(a, MOD - 2);
}

int main(void)
{
    scanf("%d %d %d", &n, &m, &v);

    initial.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &initial[i]);

    ll ans = 1;
    for (int i = 0; i < n; i++) {
        ll u = (ll)n * initial[i] % MOD + (ll)m * (i + 1) % MOD * v % MOD;
        u %= MOD;

        ans = ans * u % MOD;
    }

    ans = ans * calc_inv(calc_pow(n, n)) % MOD;

    printf("%lld\n", ans);

    return 0;
}