#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 676767677;

int N, M;

// How many ways to distribute i points to N people ?
// vector<ll> options;
// vector<ll> optionpref;

vector<ll> fact;
vector<ll> inv;

ll total = 0;

ll calc_pow(ll a, ll b) {
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

ll choose(ll n, ll k) {
    if (k < 0 || k > n) {
        return 0;
    }

    ll nom = fact[n];
    ll den = inv[k] * inv[n - k] % MOD;

    return nom * den % MOD;
}

ll distribute(ll buckets, ll stuff) {
    return choose(buckets + stuff - 1, stuff);
}

void calculate(int l, int r, int cnt) {
    if (l > r) {
        return;
    }

    int mid = (l + r) / 2;

    // Count the number of ways to get mid (use )
    ll ans = distribute(N + 1, M - 1);
    // However, we want at least one point distributed in [l, m] and one point in (m, r+1]
    if (l > 1) {
        ans -= distribute(N - (mid - l + 1) + 1, M - 1);
        ans %= MOD;
    }
    if (r < N) {
        ans -= distribute(N - (r - mid + 1) + 1, M - 1);
        ans %= MOD;
    }
    if (l > 1 && r < N) {
        ans += distribute(N - (r - l + 2) + 1, M - 1);
    }
    ans = (ans % MOD + MOD) % MOD;
    ans = (ans * cnt) % MOD;

    total = (total + ans) % MOD;

    if (l != r) {
        calculate(l, mid - 1, cnt + 1);
        calculate(mid + 1, r, cnt + 1);
    }
}

void calculate_factorials(void) {
    fact[0] = 1;
    for (int i = 1; i < fact.size(); i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv[fact.size() - 1] = calc_pow(fact[fact.size() - 1], MOD - 2);
    for (int i = fact.size() - 2; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

void solve(void) {
    scanf("%d %d", &N, &M);

    // options.resize(M + 1);
    // optionpref.resize(M + 1);
    fact.resize(N + M + 10);
    inv.resize(N + M + 10);
 
    calculate_factorials();

    // options[0] = 1;
    // optionpref[0] = options[0];

    // for (int i = 1; i <= M; i++) {
    //     options[i] = choose(N - 1 + i, i);
    //     optionpref[i] = (optionpref[i - 1] + options[i]) % MOD;
    // }

    total = 0;
    calculate(1, N, 1);

    printf("%lld\n", total);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}