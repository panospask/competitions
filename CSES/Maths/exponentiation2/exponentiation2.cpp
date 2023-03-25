#include <bits/stdc++.h>
#define MOD 1000000007

using namespace std;

typedef long long int ll;

int calc_power(ll a, int b, int mod)
{
    a %= mod;
    ll x = 1;

    while (b > 0) {
        if (b % 2) {
            x *= a;
            x %= mod;
        }

        a *= a;
        a %= mod;
        b /= 2;
    }

    return x;
}

int n;

int main(void)
{
    scanf("%d", &n);
    int a, b, c;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &a, &b, &c);

        // Calculate powers using fermats theorem
        int pow_of_a = calc_power(b, c, MOD - 1);
        int ans = calc_power(a, pow_of_a, MOD);

        printf("%d\n", ans);
    }

    return 0;
}