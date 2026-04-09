#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int BITS = 29;

int N;
vector<ll> A, B;
vector<int> cnt;

vector<ll> fact;
vector<ll> inv;

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
    ll nom = fact[n];
    ll den = inv[k] * inv[n - k] % MOD;

    return nom * den % MOD;
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
    scanf("%d", &N);

    A.assign(N, 0);
    B.resize(N);
    cnt.assign(BITS, 0);
    fact.resize(N + 1);
    inv.resize(N + 1);

    calculate_factorials();

    for (int i = 0; i < N; i++) {
        scanf("%lld", &B[i]);
    }

    for (int i = N - 1; i >= 0; i--) {
        int l = i + 1;

        // Remove infuence
        for (int b = 0; b < BITS; b++) {
            if (cnt[b]) {
                B[i] -= choose(cnt[b], l) * (1 << b) % MOD;
            }
        }

        B[i] = (B[i] % MOD + MOD) % MOD;

        for (int b = 0; b < BITS; b++) {
            if (CHECK_BIT(B[i], b)) {
                cnt[b] = l;
                for (int i = 0; i < l; i++) {
                    A[i] = A[i] | (1 << b);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%lld ", A[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}