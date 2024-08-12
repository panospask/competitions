#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int MAXN = 2e7 + 10;

int N, M, l, f;
vector<int> primes;
vector<bool> isprime;
vector<int> prev_prime;

int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    }

    return gcd(b, a % b);
}

void solve(void)
{
    scanf("%d %d %d %d", &N, &M, &l, &f);

    if (l < f) {
        swap(l, f);
    }

    int p1 = prev_prime[N];
    int p2 = p1 - 1;

    ll ans = 0;
    while (p1 <= N) {
        ans = max(ans, (ll)l * p1 + f * p2);

        p1++;
        while (gcd(p1, p2) > 1) {
            p2--;
        }
        while (gcd(p1, p2) <= 1) {
            p2++;
        }
        p2--;
    }

    printf("%lld\n", ans);
}

void sieve(void)
{
    isprime.assign(MAXN + 1, true);
    prev_prime.assign(MAXN + 1, 0);

    isprime[1] = true;

    for (int i = 2; i <= MAXN; i++) {
        if (isprime[i]) {
            primes.pb(i);
        }

        for (int j = 0; j < primes.size() && i * primes[j] <= MAXN; j++) {
            isprime[i * primes[j]] = false;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }

    prev_prime[2] = 2;
    prev_prime[1] = 1;
    for (int i = 3; i <= MAXN; i++) {
        if (isprime[i]) {
            prev_prime[i] = i;
        }
        else {
            prev_prime[i] = prev_prime[i - 1];
        }
    }
}

int main(void)
{
    sieve();

    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}