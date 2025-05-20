#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;
const int MAXV = 1000;

int N, K;
vector<int> s;

//dp[i][j]: Number of ways to flick j times in the suffix starting at i
vector<vector<ll>> dp;

vector<vector<ll>> choose;

void precalculate(void) {
    choose.assign(MAXV + 1, vector<ll>(MAXV + 1, 0));
    choose[0][0] = 1;

    for (int i = 1; i <= MAXV; i++) {
        choose[i][0] = choose[i][i] = 1;
        for (int k = 1; k < i; k++) {
            choose[i][k] = (choose[i - 1][k - 1] + choose[i - 1][k]) % MOD;
        }
    }
}

void solve(void) {
    scanf("%d %d", &N, &K);

    s.resize(N);
    dp.assign(N + 1, vector<ll>(K + 1, 0));

    for (int i = 0; i < N; i++) {
        scanf("%1d", &s[i]);
    }

    // precalculate();

    dp[N][0] = 1;
    for (int i = N - 1; i >= 0; i--) {
        dp[i][0] = 1;
        for (int j = 1; j <= K; j++) {
            // Find dp[i][j]

            // Are we able to flip before anything else?
            int able = (s[i] == 0);
            for (int bef = 0; bef <= j; bef++) {
                // We flip before exactly bef times and the current bit exactly cur times
                int cur = j - bef;

                // Find possible location of current flips given a (random) sequence of flips before
                int total = bef;
                if (able) {
                    // The first flip can happen without previous flip in front --> Add a pseudo previous flip to take with the first current flip 
                    total++;
                }

                if (total < cur) {
                    continue;
                }

                // Create pairings of "unmatched" previous flips
                int unmatched = (total - cur) / 2;

                ll ans = dp[i + 1][bef] * choose[cur + unmatched][unmatched] % MOD;
                dp[i][j] = (dp[i][j] + ans) % MOD;
            }
        }
    }

    printf("%lld\n", dp[0][K]);
}

int main(void) {
    int t;
    scanf("%d", &t);

    precalculate();

    while (t--) {
        solve();
    }

    return 0;
}