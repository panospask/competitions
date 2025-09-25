#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e6;

int N, K;
vector<vector<int>> kids;
vector<int> par;

vector<int> dep;
// cnt by depth
vector<int> cnt;

void dfs(int node) {
    cnt[dep[node]]++;
    for (auto kid : kids[node]) {
        dep[kid] = dep[node] + 1;
        dfs(kid);
    }
}

bool test(int x) {
    // At most sqrt(N) distinct values

    vector<int> dp(K + 1, -1);

    int d = 0;
    dp[0] = INF;
    int sum = 0;
    while (d < x) {
        int v = cnt[d];
        int times = 0;
        while (d < x && cnt[d] == v) {
            sum += cnt[d];
            d++;
            times++;
        }

        for (int i = 0; i <= K; i++) {
            if (dp[i] != -1) {
                // Available uses
                dp[i] = times;
            }
        }

        for (int i = 0; i + v <= K; i++) {
            dp[i + v] = max(dp[i + v], dp[i] - 1);
        }
    }

    int opt = K;
    while (dp[opt] == -1) {
        opt--;
    }

    return N - K >= sum - opt;
}

void solve(void) {
    scanf("%d %d", &N, &K);
    
    if (K > N - K) {
        K = N - K;
    }

    kids.assign(N, vector<int>());
    par.assign(N, 0);
    dep.resize(N);
    cnt.assign(N, 0);

    for (int i = 1; i < N; i++) {
        scanf("%d", &par[i]);
        par[i]--;

        kids[par[i]].pb(i);
    }

    dep[0] = 0;
    dfs(0);

    int l = 1;
    int r = N + 1;

    for (int i = 0; i < N; i++) {
        if (kids[i].size() == 0) {
            r = min(r, dep[i] + 2);
        }
    }

    while (l + 1 < r) {
        int mid = (l + r) / 2;

        if (test(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%d\n", l);

    return;
}   

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}