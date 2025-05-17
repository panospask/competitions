#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N;

vector<int> a, b;
vector<vector<int>> h;
vector<vector<int>> h_inv;

bool compatible(vector<int>& a, vector<int>& b, int a_mod, int b_mod) {
    for (int i = 0; i < N; i++) {
        if (a[i] + a_mod == b[i] + b_mod) {
            return false;
        }
    }

    return true;
}

ll calculate(vector<vector<int>>& h, vector<int>& costs) {
    vector<vector<ll>> dp(N, vector<ll>(2, INF));
    dp[0][0] = 0;
    dp[0][1] = costs[0];

    for (int i = 1; i < N; i++) {
        for (int prv = 0; prv < 2; prv++) {
            if (dp[i - 1][prv] == INF) {
                continue;
            }
            for (int cur = 0; cur < 2; cur++) {
                if (compatible(h[i - 1], h[i], prv, cur)) {
                    dp[i][cur] = min(dp[i][cur], dp[i - 1][prv] + costs[i] * cur);
                }
            }
        }
    }

    return min(dp[N - 1][0], dp[N - 1][1]);
}

void solve(void) {
    scanf("%d", &N);

    h.assign(N, vector<int>(N));
    h_inv.assign(N, vector<int>(N));
    a.resize(N);
    b.resize(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &h[i][j]);
            h_inv[j][i] = h[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    ll r1 = calculate(h, a);
    ll r2 = calculate(h_inv, b);

    if (r1 == INF || r2 == INF) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", r1 + r2);
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