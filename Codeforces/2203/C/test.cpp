#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1LL << pos))

using namespace std;

typedef __uint128_t ll;

const int BITS = 61;

long long S, M;

//until when is this used?
vector<ll> used;

bool check(ll rounds, int b) {
    ll s = 0;

    for (int c = b; c >= 0; c--) {
        if (used[c] == -1 || used[c] > rounds) {
            continue;
        }

        s += (rounds - used[c]) * (1LL << c);
    }

    return s >= (1LL << b);
}

void solve(void) {
    scanf("%lld %lld", &S, &M);

    long long ans = 0;
    used.assign(BITS, -1);
    int prv = -1;

    for (int b = 0; b < BITS; b++) {
        if (CHECK_BIT(M, b)) {
            used[b] = 0;
            prv = b;
        }

        if (CHECK_BIT(S, b) == 0) {
            continue;
        }

        if (prv == -1) {
            printf("-1\n");
            return;
        }

        ll l = 0;
        ll r = (1LL << (b - prv)) + used[prv];
        while (l + 1 < r) {
            ll mid = (l + r) / 2;
            if (check(mid, b)) {
                r = mid;
            }
            else {
                l = mid;
            }
        }

        // Distribute upon b with r rounds
        ll left = 1LL << b;
        for (int c = b; c >= 0; c--) {
            if (used[c] == -1) {
                continue;
            }
            ll v = (1LL << c);

            ll t = min((ll)r - used[c], left / v);

            left -= v * t;
            used[c] += t;
        }

        ans = max((ll)ans, r);
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