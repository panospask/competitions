#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
vector<vector<int>> adj_list;
// dp[i]: Number of ways to paint node i black (considering only the SUBTREE of i wrt 0)
vector<ll> dp;
vector<ll> ans;

void dfs(int node, int par) {
    dp[node] = 1;

    for (auto kid : adj_list[node]) {
        if (kid == par) {
            continue;
        }

        dfs(kid, node);
        dp[node] = dp[node] * (1 + dp[kid]) % M;
    }
}

void reroot(int node, int par, ll par_dp) {
    ans[node] = dp[node] * (1 + par_dp) % M;

    // Pref is 1-based, suff is 0-based
    vector<ll> pref(adj_list[node].size() + 1);
    vector<ll> suff(adj_list[node].size() + 1);
    pref[0] = 1;
    suff.back() = 1;
    for (int i = 1; i < pref.size(); i++) {
        ll v = adj_list[node][i - 1] == par ? (1 + par_dp) : (1 + dp[adj_list[node][i - 1]]);
        pref[i] = pref[i - 1] * v % M;
    }
    for (int i = adj_list[node].size() - 1; i >= 0; i--) {
        ll v = adj_list[node][i] == par ? (1 + par_dp) : (1 + dp[adj_list[node][i]]);
        suff[i] = suff[i + 1] * v % M;
    }

    for (int i = 0; i < adj_list[node].size(); i++) {
        ll cur_dp = pref[i] * suff[i + 1] % M;
        if (adj_list[node][i] != par) {
            reroot(adj_list[node][i], node, cur_dp);
        }
    }
}

int main(void) {
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    dp.resize(N);
    ans.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1);
    reroot(0, -1, 0);

    for (int i = 0; i < N; i++) {
        printf("%lld\n", ans[i]);
    }
}