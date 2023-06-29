#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, MOD;

vector<ll> fact;

int main(void)
{
    scanf("%d %d", &n, &MOD);

    fact.resize(n + 1);

    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;

    ll ans = 1;

    for (int i = 1; i <= n; i++) {
        ans = (ans * i % MOD) + (i % 2 ? -1 : 1);
        ans %= MOD;

        printf("%lld ", (ans + MOD) % MOD);
    }
    printf("\n");

    return 0;
}