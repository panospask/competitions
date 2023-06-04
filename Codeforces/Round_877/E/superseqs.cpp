#include <bits/stdc++.h>
#define MOD ((int)1e9 +7)

using namespace std;

typedef long long ll;

int n, m, k;

ll calc_pow(ll a, ll b)
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
ll modinv(ll a)
{
    return calc_pow(a, MOD - 2);
}

void solve(void)
{
    scanf("%d %d %d", &n, &m, &k);

    int tmp;
    for (int i = 0; i < n; i++)
        scanf("%d", &tmp);

    ll ans = 1;

    ans = ans * calc_pow(k, m - n) % MOD;

    ll nom = 1;
    for (int i = m; i > m - n; i--)
        nom = nom * i % MOD;

    ll den = 1;
    for (int i = 1; i <= n; i++)
        den = den * i % MOD;

    ans = ans * nom % MOD;
    ans = ans * modinv(den) % MOD;

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}