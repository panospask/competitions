#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXN = 1e6;

typedef long long ll;

// primes and their powers up to MAXN
vector<vector<int>> primes;

// power of the smallest prime in the prime decomposition of i
int cnt[MAXN + 1];

/* f[i]:
 * Sum of gcd(i, j) for each j < i
 * Calculate using eulers phi function and analyzing i to its divisors
 */
ll f[MAXN + 1];
ll pref[MAXN + 1];

// Calculates function f for the value primes[j][c]
ll primepowerf(int j, int c)
{
    return c * (primes[j][c] - primes[j][c - 1]) + primes[j][c];
}

int main(void)
{
    f[1] = 1;
    for (int i = 2; i <= MAXN; i++) {
        if (cnt[i] == 0) {
            // There is no prime decomposition => i is prime
            primes.pb({1});
            while (i * primes.back().back() <= MAXN) {
                primes.back().pb(primes.back().back() * i);
            }

            cnt[i] = 1;
            f[i] = 2 * i - 1;
        }

        for (int j = 0; j < primes.size() && primes[j][1] * i <= MAXN; j++) {
            // Compute values for the number i * primes[j][1]

            if (i % primes[j][1] == 0) {
                cnt[i * primes[j][1]] = cnt[i] + 1;

                // Trick learned in linear sieve blog
                f[i * primes[j][1]] = f[i / primes[j][cnt[i]]] * primepowerf(j, cnt[i] + 1);

                // All primes bigger than j will not be the smallest in their numbers
                break;
            }
            else {
                // f is multiplicative as the dirchlet convolution of multiplicative funtions
                f[i * primes[j][1]] = f[i] * f[primes[j][1]];
                cnt[i * primes[j][1]] = 1;
            }
        }

    }
        
    // Remove gcd(i, i) as per the problem statement
    for (int i = 1; i <= MAXN; i++) {
        f[i] -= i;
    }

    pref[0] = 0;
    for (int i = 1; i <= MAXN; i++) {
        pref[i] = f[i] + pref[i - 1];
    }

    int q;
    scanf("%d", &q);

    while (q != 0) {
        printf("%lld\n", pref[q]);
        scanf("%d", &q);
    }

    return 0;
}