#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int BITS = 30;
typedef long long ll;

int N, Q;
vector<int> A;

void solve(void) {
    scanf("%d %d", &N, &Q);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    sort(A.rbegin(), A.rend());

    vector<int> best = vector<int>(A.begin(), A.begin() + min(BITS, (int)A.size()));
    reverse(best.begin(), best.end());

    while (Q--) {
        vector<int> cur = best;

        int X;
        scanf("%d", &X);

        ll ans = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            if (!CHECK_BIT(X, b)) {
                continue;
            }

            int v = cur.back();
            cur.pop_back();
            if (v >= (1LL << (b + 1))) {
                // We're done
                break;
            }
            if (v >= (1 << b)) {
                // Not done, but don't pay anything
                v -= (1 << b);
                
            }
            else {
                // Pay
                ans += ((1 << b) - v);
                v = 0;
            }
            int p = 0;
            while (p < cur.size() && v > cur[p]) {
                p++;
            }
            cur.insert(cur.begin() + p, v);
        }

        printf("%lld\n", ans);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}