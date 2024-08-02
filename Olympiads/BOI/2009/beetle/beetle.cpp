/* Sort explaination because I was stuck on this problem two times in two different summers
 * The beetle must drink from 0 to N drops, assume the beetle drinks i drops and calculate the optimal
 * way to do so.
 */

#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, M;
vector<int> lx;
vector<int> rx;

// dp[l][r][k]: The minimum value lost while drink all drops from lx[l] to rx[r]
// k == 0: The beetle is at lx[l]
// k == 1: The beetle is at rx[r]
vector<vector<vector<ll>>> dp;

ll test_drops(int drops)
{
    ll res = INF;

    dp.assign(lx.size(), vector<vector<ll>>(rx.size(), vector<ll>(2, INF)));

    dp[0][0][0] = dp[0][0][1] = 0;
    for (int l = 0; l < lx.size(); l++) {
        for (int r = 0; r < rx.size(); r++) {
            for (int k = 0; k < 2; k++) {
                int len = r + l;
                if (len > drops) {
                    continue;
                }
                else if (len == drops) {
                    res = min(res, dp[l][r][k]);
                }

                int position = k == 0 ? lx[l] : rx[r];

                // All the remaing drops will lose value during the next move
                int remaining = drops - len;

                // Either move one to the left or one to the right
                if (l + 1 < lx.size()) {
                    int dist = abs(position - lx[l + 1]);
                    dp[l + 1][r][0] = min(dp[l + 1][r][0], dp[l][r][k] + (ll)dist * remaining);
                }
                if (r + 1 < rx.size()) {
                    int dist = abs(position - rx[r + 1]);
                    dp[l][r + 1][1] = min(dp[l][r + 1][1], dp[l][r][k] + (ll)dist * remaining);
                }
            }
        }
    }

    return res;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    lx.pb(0);
    rx.pb(0);

    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);

        if (x < 0) {
            lx.pb(x);
        }
        else {
            rx.pb(x);
        }
    }

    sort(lx.rbegin(), lx.rend());
    sort(rx.begin(), rx.end());

    ll ans = 0;
    for (int drops = 0; drops <= N; drops++) {
        ans = max(ans, (ll)drops * M - test_drops(drops));
    }

    printf("%lld\n", ans);

    return 0;
}