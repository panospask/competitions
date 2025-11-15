#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

ll ceil(ll a, ll b) {
    return (a + b - 1) / b;
}

struct Line {
    ll a, b;
    int idx;

    ll eval(int x) {
        return a * x + b;
    }
};

ll intersect(Line l1, Line l2) {
    return ceil(l2.b - l1.b, l1.a - l2.a);
}

int N, K;
vector<int> A;
vector<int> pref;

vector<ll> prv;
// dp[i]: Given that prv stores optimal answer for c - 1 states, dp calculates the optimal answer for each i, if we use c states
vector<ll> dp;

// Optimal previous splits for all dp states
vector<vector<int>> opt;

deque<Line> hull;

int main(void) {
    scanf("%d %d", &N, &K);

    A.resize(N + 1);
    pref.resize(N + 1);
    opt.assign(K + 1, vector<int>(N + 1));

    pref[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        pref[i] = pref[i - 1] + A[i];
    }
    
    prv.assign(N + 1, 0);
    dp.assign(N + 1, 0);
    for (int c = 1; c <= K; c++) {
        hull.clear();
        swap(dp, prv);

        // Insert the default (ie split at first c - 1 spots)
        hull.pb({pref[c - 1], prv[c - 1] - (ll)pref[c  - 1] * pref[N], c - 1});
        for (int i = 1; i < c; i++) {
            dp[i] = -1;
        }
        for (int i = c; i <= N; i++) {
            while (hull.size() >= 2) {
                if (hull[0].eval(pref[i]) <= hull[1].eval(pref[i])) {
                    hull.pop_front();
                }
                else {
                    break;
                }
            }

            dp[i] = (ll)(pref[N] - pref[i]) * pref[i] + hull[0].eval(pref[i]);
            opt[c][i] = hull[0].idx;

            if (pref[i] == pref[i - 1]) {
                // This spot contributes nothing!!
                continue;
            }

            Line cur = {pref[i], prv[i] - (ll)pref[i] * pref[N], i};
            int sz = hull.size();
            while (sz >= 2) {
                if (intersect(hull[sz - 2], hull[sz - 1]) >= intersect(hull[sz - 1], cur)) {
                    hull.pop_back();
                    sz--;
                }
                else {
                    break;
                }
            }
            hull.pb(cur);
        }

    }

    int best = 1;
    for (int i = 1; i <= N; i++) {
        if (dp[i] > dp[best]) {
            best = i;
        }
    }

    printf("%lld\n", dp[best]);
    while (best) {
        printf("%d ", best);
        best = opt[K][best];
        K--;
    }
    printf("\n");
}