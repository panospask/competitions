#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

ll A, B;

ll calc_power(ll a, ll b)
{
    // MOD is prime so we can modify b using Ferma's Little Theorem
    b %= MOD - 1;
    a %= MOD;

    ll c = 1;

    while (b) {
        if (b & 1) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    assert(c > 0);
    return c;
}

ll calc_inv(ll a)
{
    return calc_power(a, MOD - 2);
}

int main(void)
{
    freopen("sumdiv.in", "r", stdin);
    freopen("sumdiv.out", "w", stdout);

    scanf("%lld %lld", &A, &B);

    ll S = 1;
    ll B_orignal = B;
    B %= MOD - 1;

    for (int i = 2; (ll)i * i <= A; i++) {
        if (A % i == 0) {
            int cnt = 0;
            while (A % i == 0) {
                cnt++;
                A /= i;
            }

            S = S * (calc_power(i, B * cnt + 1) - 1) % MOD * calc_inv(i - 1) % MOD;
        }
    }

    // Remaining A is either 1 or prime
    if (A != 1) {
        // A is prime --> Add to the divisors

        if ((A - 1) % MOD != 0) {
            // A-1 is coprime to MOD, act normally
            S = S * (calc_power(A, B + 1) - 1) % MOD * calc_inv(A - 1) % MOD;
        }
        else {
            // A-1 is not coprime to MOD, inverse does not exist
            // A % MOD = 1

            S = S * (A % MOD) % MOD * (B_orignal % MOD + 1) % MOD;
        }
    }

    S = (S % MOD + MOD) % MOD;

    printf("%lld\n", S);

    return 0;
}