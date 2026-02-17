#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1LL << pos))

using namespace std;

typedef long long ll;

const int BITS = 60;

int N;
vector<ll> A;

vector<ll> basis;
vector<int> cnt;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    basis.assign(BITS, 0);
    cnt.assign(BITS, 0);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);

        for (int b = 0; b < BITS; b++) {
            if (CHECK_BIT(A[i], b)) {
                cnt[b]++;
            }
        }
    }

    bool found = false;
    for (int b = BITS - 1; b >= 0 && !found; b--) {
        if (cnt[b] != 0) {
            found = true;
            if (cnt[b] % 2 == 1) {
                ll sum = 0;
                for (int i = 0; i < N; i++) {
                    sum = sum ^ A[i];
                }
                printf("%lld\n", sum);
                return;
            }
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int b = 0; b < BITS; b++) {
            if (CHECK_BIT(A[i], b) && cnt[b] % 2 == 1) {
                A[i] -= (1LL << b);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int b = BITS - 1; b >= 0; b--) {
            if (CHECK_BIT(A[i], b) == 0) {
                continue;
            }

            if (!basis[b]) {
                basis[b] = A[i];
                break;
            }
            else {
                A[i] ^= basis[b];
            }
        }
    }

    ll ans = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        if (basis[b] == 0) {
            continue;
        }

        if (!CHECK_BIT(ans, b)) {
            ans = ans ^ basis[b];
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}