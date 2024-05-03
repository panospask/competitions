#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<int> a;

// dp[i][j]: Best we can do up to i (i is not included) with j swaps
vector<vector<ll>> dp;
vector<vector<ll>> best;

vector<ll> pref;

ll sum(int i, int j)
{
    return pref[j + 1] - pref[i];
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);
    dp.assign(N + 1, vector<ll>(K + 1, 0));
    best.assign(N, vector<ll>(K + 1, -1));
    pref.resize(N + 1);

    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        pref[i + 1] = pref[i] + a[i];
    }

    for (int i = 0; i < N; i++) {
        int minv = INT_MAX;
        for (int s = 0; s <= K; s++) {
            if (i + s >= N) {
                break;
            }

            minv = min(minv, a[i + s]);
            best[i][s] = sum(i, i + s) - (ll)(s + 1) * minv;
        }
    }

    dp[0][0] = 0;
    for (int i = 0; i < N; i++) {
        for (int s = 0; s <= K; s++) {
            if (i + s >= N) {
                break;
            }

            for (int j = 0; j + s <= K; j++) {
                dp[i + s + 1][j + s] = max(dp[i + s + 1][j + s], dp[i][j] + best[i][s]);
            }
        }
    }

    printf("%lld\n", sum(0, N - 1) - dp[N][K]);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}