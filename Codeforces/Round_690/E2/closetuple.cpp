#include <bits/stdc++.h>

using namespace std;

const int MOD = ((int)1e9 + 7);

typedef long long ll;

int n, m, k;

ll ans = 0;

vector<int> a;

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

void precalc_fact(void)
{
    fact.resize(n + 1);
    inv.resize(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;

    inv[n] = calc_inv(fact[n]);
    for (int i = n - 1; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}

ll choose(int n, int m)
{
    if (n < m)
        return 0;

    ll nom = fact[n];
    ll den = inv[m] * inv[n - m] % MOD;

    return nom * den % MOD;
}

void solve(void)
{
    ans = 0;

    scanf("%d %d %d", &n, &m, &k);

    precalc_fact();

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());

    int latest_max = -1;
    for (int i = 0; i < n; i++) {
        int cur = latest_max;
        while (cur < n - 1 && a[cur + 1] - a[i] <= k)
            cur++;

        ans += choose(cur - i + 1, m) - choose(latest_max - i + 1, m);
        ans = (ans + MOD) % MOD;
        latest_max = cur;
    }

    printf("%lld\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}