#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

typedef long long int ll;

int n;

int calc_power(ll a, ll b, int mod)
{
    a %= mod;
    ll x = 1;

    while (b > 0) {
        if (b % 2)
            x = x * a % mod;
        
        a = a * a % mod;
        b /= 2;
    }

    return x;
}

int find_inv(ll a, int mod)
{
    a %= mod;

    return calc_power(a, mod - 2, mod);
}

int main(void)
{
    scanf("%d", &n);
    ll t = 1, s = 1, p = 1;
    ll alt_t = 1;

    ll num = 1;
    ll pos_root = 1;
    bool hasroot = true;


    long long int x, k;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &x, &k);

        if (k % 2)
            hasroot = false;

        t = (t * (k +1)) % MOD;

        s = ((s * (calc_power(x, k+1, MOD) - 1)) %MOD) * (find_inv(x-1, MOD)) %MOD; 
        
        p = ((long long int)calc_power(p, k+1, MOD) * calc_power(calc_power(x, (k * (k+1) / 2), MOD), alt_t, MOD)) % MOD; 

        alt_t = (alt_t * (k+1)) % (MOD - 1); 
        num = num * calc_power(x, k, MOD) % MOD;
    }

    printf("%lld %lld %lld\n", t, s, p);

    return 0;
}