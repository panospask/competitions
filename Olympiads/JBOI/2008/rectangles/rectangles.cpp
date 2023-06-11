#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const ll INF = 1e13;

int n;
vector<pi> rectangles;

// dp[i][false] : first side up
// dp[i][true] : second side up
vector<vector<ll>> dp;

int main(void)
{
    scanf("%d", &n);
    rectangles.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &rectangles[i].f, &rectangles[i].s);
    }

    dp.assign(n, vector<ll>(2, -1));
    dp[0][false] = rectangles[0].f;
    dp[0][true] = rectangles[0].s;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            int topside = rectangles[i].f;
            int horside = rectangles[i].s;
            if (j) {
                swap(topside, horside);
            }

            for (int c = 0; c < 2; c++) {
                int prvhor = !c ? rectangles[i - 1].s : rectangles[i - 1].f;

                dp[i][j] = max(dp[i][j], dp[i - 1][c] + topside + abs(prvhor - horside));
            }
        }
    }

    ll ans = max(dp[n - 1][false], dp[n - 1][true]);

    printf("%lld\n", ans);

    return 0;
}