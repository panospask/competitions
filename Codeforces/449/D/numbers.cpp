#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;

const int BITS = 20;
const int MOD = 1e9 + 7;

int N;
vector<int> A;
vector<int> superset;

ll calc_pow(ll a, int b) {
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    superset.resize(1 << BITS);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        superset[A[i]]++;
    }

    for (int b = 0; b < BITS; b++) {
        for (int mask = 0; mask < (1 << BITS); mask++) {
            if (CHECK_BIT(mask, b) == 0) {
                superset[mask] += superset[mask + (1 << b)];
            }
        }
    }

    ll ans = 0;
    for (int mask = 0; mask < (1 << BITS); mask++) {
        int cnt = 0;
        for (int b = 0; b < BITS; b++) {
            if (CHECK_BIT(mask, b)) {
                cnt++;
            }
        }

        if (cnt % 2 == 0) {
            ans += calc_pow(2, superset[mask]);
        }
        else {
            ans -= calc_pow(2, superset[mask]);
        }
        ans %= MOD;
    }

    if (ans < 0) {
        ans += MOD;
    }

    printf("%lld\n", ans);
    
    return 0;
}