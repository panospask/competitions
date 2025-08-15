#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, b;
vector<vector<int>> kids;
vector<int> c, d;

vector<vector<ll>> dp[2];

void merge(vector<ll>& a, vector<ll>& b) {
    vector<ll> res(a.size() + b.size() - 1, INF);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            res[i + j] = min(res[i + j], a[i] + b[j]);
        }
    }

    a = res;
}

void dfs(int node, int par) {
    dp[0][node] = {0, c[node]};
    dp[1][node] = {INF, c[node] - d[node]};

    for (auto neigh : kids[node]) {
        dfs(neigh, node);

        for (int i = 0; i < dp[0][neigh].size(); i++) {
            dp[1][neigh][i] = min(dp[1][neigh][i], dp[0][neigh][i]);
        }

        merge(dp[0][node], dp[0][neigh]);
        merge(dp[1][node], dp[1][neigh]);
    }
}

int main(void) {
    scanf("%d %d", &N, &b);

    c.resize(N);
    d.resize(N);
    kids.resize(N);
    dp[0].resize(N);
    dp[1].resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &c[i], &d[i]);
        if (i) {
            int x;
            scanf("%d", &x);
            x--;
            kids[x].pb(i);
        }
    }

    dfs(0, -1);
    for (int i = 0; i < dp[0][0].size(); i++) {
        dp[1][0][i] = min(dp[1][0][i], dp[0][0][i]);
    }

    int ans = upper_bound(dp[1][0].begin(), dp[1][0].end(), b) - dp[1][0].begin() - 1;
    printf("%d\n", ans);

    return 0;
}