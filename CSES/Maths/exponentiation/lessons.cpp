#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

ll exponentiation(ll a, ll b) {
    ll res = 1;
    ll apow = a;

    while (b) {
        int cur = b % 2;
        if (cur) {
            res = res * apow % MOD;
        }

        apow = apow * apow % MOD;
        b /= 2;
    }

    return res;
}

int N;

int main(void) {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        ll a, b;
        scanf("%lld %lld", &a, &b);

        printf("%lld\n", exponentiation(a, b));
    }
}