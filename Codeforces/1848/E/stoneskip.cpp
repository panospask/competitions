#include <bits/stdc++.h>

using namespace std;

const int MAXC = 1e6 + 1;

typedef long long ll;

int x, Q, M;

vector<int> primes;
vector<ll> odd_divisors;
vector<int> smallest_div;

void calculate_primes(void)
{
    smallest_div.assign(MAXC, -1);

    for (int i = 2; i < MAXC; i++) {
        if (smallest_div[i] == -1) {
            primes.push_back(i);
            smallest_div[i] = i;
        }

        for (int j = 0; j < primes.size() && i * primes[j] < MAXC; j++) {
            smallest_div[i * primes[j]] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }

    odd_divisors.assign(MAXC, 1);
    for (int i = 2; i < MAXC; i++) {
        if (i % 2 == 0) {
            odd_divisors[i] = odd_divisors[i / 2];
        }
        else {
            int cur = i;
            int cnt = 0;
            int p = smallest_div[i];
            while (cur % p == 0) {
                cnt++;
                cur /= p;
            }

            odd_divisors[i] = odd_divisors[cur] * (cnt + 1) % M;
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &x, &Q, &M);

    calculate_primes();

    ll ans = 0;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            if (i % 2)
                ans++;
            if ((x / i) % 2 && i * i != x)
                ans++;
        }
    }

    while (Q--) {
        int x;
        scanf("%d", &x);

        ans = ans * odd_divisors[x] % M;

        printf("%lld\n", ans);
    }

    return 0;
}