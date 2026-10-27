#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, M;
vector<int> neg, pos;
vector<int> x;

vector<vector<vector<ll>>> dp;

int main(void) {
    scanf("%d %d", &N, &M);

    x.resize(N);
    neg.push_back(0);
    pos.push_back(0);
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);

        if (x[i] < 0) {
            neg.push_back(-x[i]);
        }
        else {
            pos.push_back(x[i]);
        }
    }
    sort(neg.begin(), neg.end());
    sort(pos.begin(), pos.end());

    ll ans = 0;
    for (int K = 0; K <= N; K++) {
        dp.assign((int)neg.size() + 1, vector<vector<ll>>((int)pos.size() + 1, vector<ll>(2, INF)));

        // ans = K * M - dp[..][..]
        dp[0][0][0] = 0;
        for (int total = 1; total <= K; total++) {
            for (int l = 0; l <= min((int)neg.size() - 1, total); l++) {
                int r = total - l;
                if (r >= pos.size()) {
                    continue;
                }
                if (l == 0 && r == 0) {
                    dp[l][r][0] = dp[l][r][1] = 0;
                    continue;
                }
                int rem = K - (l + r);
                if (rem < 0) {
                    continue;
                }

                if (l != 0) {
                    // From state (l - 1, r)
                    int rem = K - ((l - 1) + r);
                    ll loss1 = dp[l - 1][r][0] + (ll)abs(-neg[l] + neg[l - 1]) * rem;
                    ll loss2 = dp[l - 1][r][1] + (ll)abs(-neg[l] - pos[r]) * rem;

                    dp[l][r][0] = min(loss1, loss2);
                }
                if (r != 0) {
                    // From state (l, r - 1)
                    int rem = K - (l + (r - 1));
                    ll loss1 = dp[l][r - 1][0] + (ll)abs(pos[r] + neg[l]) * rem;
                    ll loss2 = dp[l][r - 1][1] + (ll)abs(pos[r] - pos[r - 1]) * rem;

                    dp[l][r][1] = min(loss1, loss2);
                }

                dp[l][r][0] = min(dp[l][r][0], dp[l][r][1] + (K - rem) * abs(neg[l] + pos[r]));
                dp[l][r][1] = min(dp[l][r][1], dp[l][r][0] + (K - rem) * abs(neg[l] + pos[r]));

                if (rem == 0) {
                    ans = max(ans, (ll)K * M - min(dp[l][r][0], dp[l][r][1]));
                }
            }
        }
    }

    printf("%lld\n", ans);
}