#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

const int MAXV = 1e6;
const int MOD = 1e9 + 7;

int N;
vector<int> A;
vector<int> left_turns;
vector<int> right_turns;

// Helper arrays for implementing choose function
vector<ll> fact, inv;

ll calc_pow(ll a, int b)
{
    ll c = 1;

    while (b) {
        if (b & 1) {
            c = c * a % MOD;
        }

        b = (b >> 1);
        a = a * a % MOD;
    }

    return c;
}

void precalculate_factorials(void)
{
    fact.resize(MAXV + 1);
    inv.resize(MAXV + 1);

    fact[0] = 1;
    for (int i = 1; i <= MAXV; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv[MAXV] = calc_pow(fact[MAXV], MOD - 2);
    for (int i = MAXV - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

ll choose(int a, int b)
{
    assert(a >= b);
    if (b < 0) {
        return 1;
    }

    return fact[a] * inv[b] % MOD * inv[a - b] % MOD;
}

int main(void)
{
    scanf("%d", &N);

    A.resize(N + 1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    A[N] = 0;
    
    precalculate_factorials();

    ll ans = 1;
    for (int i = N - 1; i >= 0; i--) {
        if (A[i] % 2 || A[i] == 0) {
            printf("0\n");
            exit(0);
        }
        A[i] /= 2;

        if (A[i + 1] > A[i]) {
            ans = ans * choose(A[i + 1] - 1, A[i] - 1) % MOD;
        }
        else {
            ans = ans * choose(A[i], A[i + 1]) % MOD;
        }
    }

    printf("%lld\n", ans);

    return 0;
}