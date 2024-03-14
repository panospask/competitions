#include <bits/stdc++.h>

using namespace std;

const int MAXV = (int)1e7 * 2;

typedef long long ll;

int c, d, x;

vector<int> primes;
vector<int> minprime;

void calculate_primes(void)
{
    minprime.assign(MAXV + 1, -1);

    for (int i = 2; i <= MAXV; i++) {
        if (minprime[i] == -1) {
            primes.push_back(i);
            minprime[i] = i;
        }

        for (int j = 0; j < primes.size() && i * primes[j] <= MAXV; j++) {
            minprime[i * primes[j]] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

ll ans = 0;

void test_gcd(int g)
{
    if ((x / g + d) % c) {
        // No integer solutions
        return;
    }

    int num = (x / g + d) / c;

    assert(num <= MAXV);

    ll cur_possibilities = 1;
    while (num != 1) {
        int p = minprime[num];
        while (num % p == 0)
            num /= p;

        cur_possibilities *= 2;
    }

    ans += cur_possibilities;
}

void solve(void)
{
    ans = 0;
    scanf("%d %d %d", &c, &d, &x);

    for (int i = 1; i * i <= x; i++)
        if (x % i == 0) {
            test_gcd(i);

            if (x / i != i)
                test_gcd(x / i);
        }

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    calculate_primes();

    while (t--)
        solve();

    return 0;
}