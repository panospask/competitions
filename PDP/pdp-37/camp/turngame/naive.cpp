#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N;
ll C;

vector<int> A;
vector<pi> order;

vector<vector<ll>> dp;

int main(void) {
    scanf("%d %lld", &N, &C);

    A.resize(N);
    order.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        order[i] = {A[i], i};
    }

    dp.assign(N, vector<ll>(2, 0));

    sort(order.begin(), order.end());

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        int x = order[i].second;

        // First try left
        for (int j = 0; j < x; j++) {
            dp[x][0] = max(dp[x][0], dp[j][0]);
        }
        dp[x][0] += order[i].first;

        // Then right
        for (int j = x + 1; j < N; j++) {
            dp[x][1] = max(dp[x][1], dp[j][1]);
        }
        dp[x][1] += order[i].first;

        // Interchange them
        dp[x][0] = max(dp[x][0], dp[x][1] - C);
        dp[x][1] = max(dp[x][1], dp[x][0] - C);

        ans = max(ans, dp[x][0]);
        ans = max(ans, dp[x][1]);
    }

    printf("%lld\n", ans);

    return 0;
}