#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __uint128_t lll;

const ll MOD = (1ll << 61) - 1;
const int MAXV = 1e5;
const int P = 53;

int n, k;
vector<int> a;
vector<ll> pwr;
vector<int> primes;
vector<int> latest_div;

map<ll, int> resulting_powers;

void generate_primes(void)
{
    latest_div.assign(MAXV + 1, -1);

    for (int i = 2; i <= MAXV; i++) {
        if (latest_div[i] == -1) {
            primes.push_back(i);
            latest_div[i] = primes.size() - 1;
            for (int j = 2 * i; j <= MAXV; j += i)
                latest_div[j] = primes.size() - 1;
        }
    }
}

void calculate_pwr(void)
{
    pwr.resize(primes.size());
    pwr[0] = 1;
    for (int i = 0; i < primes.size() - 1; i++)
        pwr[i + 1] = (lll)pwr[i] * P % MOD;
}

int main(void)
{
    scanf("%d %d", &n, &k);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    generate_primes();
    calculate_pwr();
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int curv = a[i];
        ll curhash = 0;
        ll lookhash = 0;

        while (curv != 1) {
            int cnt= 0;
            int id = latest_div[curv];
            int p = primes[id];

            while (curv % p == 0) {
                cnt++;
                curv /= p;
            }

            cnt %= k;
            curhash = (curhash + (lll)cnt * pwr[id] % MOD) % MOD;
            lookhash = (lookhash + (lll)(k - cnt) % k * pwr[id] % MOD) % MOD;
        }


        ans += resulting_powers[lookhash];
        resulting_powers[curhash]++;
    }

    printf("%lld\n", ans);

    return 0;
}