#include <bits/stdc++.h>

using namespace std;

const int COLOURS = 26;

typedef long long ll;
typedef pair<int, int> pi;

int N;
vector<vector<pi>> adj_list;
vector<int> c;
vector<int> a;

ll ans;
int COLOUR;
//cnt[i]: Number of flowers inside the subtree of i
vector<ll> cnt;
//dp[i]: Number of steps required for all flowers inside the subtree of i to reach i
vector<ll> dp;

void dfs(int node, int par) {
    dp[node] = 0;
    cnt[node] = c[node] == COLOUR ? a[node] : 0;

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        dp[node] += dp[neigh] + cnt[neigh] * w;
        cnt[node] += cnt[neigh];
    }
}

void reroot(int node, int par, ll outside_dp, ll outside_cnt) {
    ans = min(ans, dp[node] + outside_dp);

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }
        ll new_dp = outside_dp + dp[node] - dp[neigh] - cnt[neigh] * w;
        ll new_cnt = outside_cnt + cnt[node] - cnt[neigh];
        new_dp += w * new_cnt;

        reroot(neigh, node, new_dp, new_cnt);
    }
}

int main(void) {
    scanf("%d", &N);

    c.resize(N);
    a.resize(N);
    adj_list.resize(N);
    dp.resize(N);
    cnt.resize(N);

    for (int i = 0; i < N; i++) {
        char col;
        scanf(" %c", &col);

        c[i] = col - 'a';
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
    }

    for (COLOUR = 0; COLOUR < COLOURS; COLOUR++) {
        ans = LLONG_MAX;

        dfs(0, 0);
        reroot(0, 0, 0, 0);

        printf("%lld ", ans);
    }
    printf("\n");

    return 0;
}