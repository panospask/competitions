#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> ii;

int n, MOD;
vector<vector<int>> adj_list;
// How many ways there are for this node to be black(connecting to all other blacks in the subtree)
vector<long long> dp;
vector<long long> dp2;
vector<vector<long long>> pref_dp;
vector<vector<long long>> suff_dp;
vector<ii> p;
vector<long long int> ans;

long long calc_pow(long long a, long long b, long long mod)
{
    long long c = 1;
    while (b) {
        if (b % 2)
            c = c * a % mod;
        a = a * a % mod;
        b /= 2;
    }

    return c;
}

void calc_dp(int node, int par, int rank)
{
    dp[node] = 1;
    pref_dp[node][0] = suff_dp[node][adj_list[node].size()] = 1;
    p[node] = mp(par, rank);
    int cnt = 0;
    for (auto neigh : adj_list[node]) {
            cnt++;
        if (neigh != par) {
            calc_dp(neigh, node, cnt);
            dp[node] = (dp[node] * (1 + dp[neigh])) % MOD;
            pref_dp[node][cnt] = 1 + dp[neigh];
            suff_dp[node][cnt] = 1 + dp[neigh];
        }
        else
            pref_dp[node][cnt] = 1;
            suff_dp[node][cnt] = 1;
    }

    for (int i = 1; i < cnt; i++) {
        pref_dp[node][i] *= pref_dp[node][i-1];
        pref_dp[node][i] %= MOD;
    }
    for (int i = cnt - 1; i >= 0; i--) {
        suff_dp[node][i] *= suff_dp[node][i+1];
        suff_dp[node][i] %= MOD;
    }
}

void dfs2(int node, int par)
{
    int cnt = adj_list[node].size();

    if (adj_list[node].size() == 1 && par != -1)
        return;

    if (adj_list[node][0] != par)
        dp2[adj_list[node][0]] = 1 + dp2[node] * suff_dp[node][1];
    for (int i = 1; i < cnt - 1; i++)
        if (adj_list[node][i] != par)
            dp2[adj_list[node][i]] = 1 + (dp2[node] * pref_dp[node][i-1] * suff_dp[node][i+1]);
    if (adj_list[node][cnt-1] != par && cnt-2 >= 0)
        dp2[adj_list[node][cnt-1]] = 1 + dp2[node] * pref_dp[node][cnt-2];

    for (int i = 0; i < cnt; i++)
        dp2[i] %= MOD;

    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs2(neigh, node);
}

int main(void)
{
    scanf("%d %d", &n, &MOD);
    dp.resize(n);
    adj_list.resize(n);
    ans.resize(n);
    p.resize(n);
    pref_dp.assign(n + 1, vector<long long>(n + 2));
    suff_dp.resize(n + 1, vector<long long>(n + 2));
    dp2.resize(n);

    if (n == 1) {
        printf("%d\n", 1);
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dp2[0] = 1;
    calc_dp(0, -1, 0);
    dfs2(0, -1);
    ans[0] = dp[0];
    for (int i = 1; i < n; i++) {
        ans[i] = dp[i] * dp2[i] % MOD;
    }

    for (int i = 0; i < n; i++)
        printf("%lld\n", ans[i]);
}