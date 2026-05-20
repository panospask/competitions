#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

const int MAXV = 1e6 + 5;
vector<ll> fact;
vector<ll> inv;

int N, Q, M;
vector<int> A;
vector<int> B;

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
ll calc_inv(ll a) {
    return calc_pow(a, MOD - 2);
}

void factorials(void) {
    fact.resize(MAXV);
    inv.resize(MAXV);

    fact[0] = 1;
    for (int i = 1; i < MAXV; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv[MAXV - 1] = calc_inv(fact[MAXV - 1]);
    for (int i = MAXV - 2; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

ll choose(int n, int k) {
    if (k > n || k < 0) {
        return 0;
    }

    ll nom = fact[n];
    ll den = inv[k] * inv[n - k] % MOD;
    return nom * den % MOD;
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int op, l, r, m;
    scanf("%d %d %d %d", &op, &l, &r, &m);
    l--; r--;

    B.resize(r - l + 1);
    for (int i = l; i <= r; i++) {
        B[i - l] = A[i];
    }

    M = r - l + 1;

    ll sum = 0;
    int cnt = 0;
    for (int i = 0; i < M; i++) {
        if (B[i] != -1) {
            sum += B[i];
        }
        else {
            cnt++;
        }
    }

    if (sum > m) {
        printf("%d\n", 0);
        return;
    }


}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}