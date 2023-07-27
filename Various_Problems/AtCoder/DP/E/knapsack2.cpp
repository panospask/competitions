#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;
const int MAXV = 1e3;

int N, W;
vector<int> w, v;

// dp[i]: Construct a knapsack with value at least i and minimum weight
vector<ll> dp;

int main(void)
{
    scanf("%d %d", &N, &W);

    v.resize(N);
    w.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }

    dp.assign(MAXV * N + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = MAXV * N; j > 0; j--) {
            if (j - v[i] >= 0) {
                dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
            }
            
            dp[j - 1] = min(dp[j - 1], dp[j]);
        }
    }

    ll ans = 0;
    for (int j = MAXV * N; j>= 0; j--) {
        if (dp[j] <= W) {
            ans = j;
            break;
        }
    }

    printf("%lld\n", ans);

    return 0;
}