#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int BITS = 20;
const int MAXCHECK = 1e6 + 1;
const int MAXFACTORS = 2e5;

int N, Q;
vector<ll> A;
vector<ll> pref;
vector<pli> primes;
int freq[MAXFACTORS] = {0};


ll gcd(ll a, ll b) {
    if (a < b) {
        swap(a, b);
    }

    while (b) {
        a = a % b;
        swap(a, b);
    }

    return a;
}

int position(ll num) {
    int code = 0;
    for (int j = 0; j < primes.size(); j++) {
        pli p = primes[j];
        int cnt = 0;
        while (num % p.first == 0) {
            cnt++;
            num /= p.first;
        }

        code = code * (p.second + 1) + cnt;
    }

    return code;
}

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    pref.resize(N + 1);
    
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
        pref[i + 1] = pref[i] + A[i];
    }
    for (int i = 0; i < N; i++) {
        pref[i] = gcd(pref[i], pref[N]);
    }

    ll total = pref[N];

    // We must now factorize total
    for (int p = 2; p < MAXCHECK; p++) {
        if (total % p == 0) {
            int cnt = 0;
            while (total % p == 0) {
                cnt++;
                total /= p;
            }

            primes.pb({p, cnt});
        }
    }
    // total is now either a semiprime or a prime

    vector<ll> queries;
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        queries.resize(Q);
        scanf("%lld", &queries[i]);
        
        if (total % queries[i] == 0 && queries[i] != 1 && queries[i] != total) {
            if (queries[i] * queries[i] == total) {
                primes.pb({queries[i], 2});
            }
            else {
                primes.pb({queries[i], 1});
                primes.pb({total / queries[i], 1});
            }

            total = 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        ll check = gcd(pref[N], total);
        if (check != 1 && check != total) {
            // We found our two primes
            if (check * check == total) {
                primes.pb({check, 2});
            }
            else {
                primes.pb({check, 1});
                primes.pb({total / check, 1});
            }

            total = 1;
        }
    }
    if (total != 1) {
        primes.pb({total, 1});
    }

    // Now create the multidimensional prefix sums. Use encoding for each number as a factor of pref[N]
    for (int i = 1; i < N; i++) {
        freq[position(pref[i])]++;
    }

    // Propagate the prefix sums, prime by prime
    // Which block should we process
    int block = 1;
    for (int i = primes.size() - 1; i >= 0; i--) {
        for (int code = position(pref[N]); code >= 0; code--) {
            // Find if code can give a prime lies in the current block
            bool inside = code / block % (primes[i].second + 1);
            if (inside) {
                freq[code - block] += freq[code];
            }
        }

        block *= (primes[i].second + 1);
    }

    int q = 0;
    while (q < Q) {
        q++;
        
        ll x = queries[q - 1];
        if (pref[N] % x != 0) {
            printf("-1\n");
            continue;
        }
        ll ans = (N - 1) + pref[N] / x - 1;
        ans -= 2 * (freq[position(x)]);

        printf("%lld\n", ans);
    }

    return 0;
}