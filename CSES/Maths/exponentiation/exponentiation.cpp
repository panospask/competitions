#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

ll calc_power(ll a, int b, int mod)
{   
    ll x = 1;
    a %= mod;

    while (b > 0) {
        if (b % 2) {
            x *= a;
            x %= mod;
        }

        a = (a * a) % mod;
        b /= 2;
    }

    return x;
}

int n;

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        printf("%lld\n", calc_power(a, b, 1000000007));
    }

    return 0;
}