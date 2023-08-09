#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int MOD = 1000002022;

int N, M;
vector<vector<int>> kids;
vector<int> status;
vector<int> a;
vector<vector<ll>> dp;

void recalculate(int node)
{
    if (node >= N)
        return;

    for (auto k : kids[node])
        recalculate(k);

    // ways[i]: Ways such that exactly i of the kids will be ON
    vector<ll> ways;
    ways.assign(kids[node].size() + 1, 0);

    ways[0] = 1;
    for (int i = 0; i < kids[node].size(); i++) {
        int k = kids[node][i];
        for (int j = i; j >= 0; j--) {
            ways[j + 1] += ways[j] * dp[k][1] % MOD;
            ways[j] = ways[j] * dp[k][0] % MOD;
        }
    }

    dp[node][1] = dp[node][0] = 0;
    ll suff = 0;
    for (int v = kids[node].size(); v > 0; v--) {
        // Set the parameter equal to v
        suff = (suff + ways[v]) % MOD;
        dp[node][1] = (dp[node][1] + suff) % MOD;
    }

    ll pref = ways[0];
    for (int v = 1; v <= kids[node].size(); v++) {
        dp[node][0] = (dp[node][0] + pref) % MOD;
        pref = (pref + ways[v]) % MOD;
    }
}

void init(int n, int m, vector<int> p, vector<int> v)
{
    N = n;
    M = m;
    a = v;

    kids.resize(N);
    dp.resize(N + M, vector<ll>(2));

    for (int i = 0; i < M; i++) {
        dp[N + i][a[i]] = 1;
        dp[N + i][!a[i]] = 0;
    }

    for (int i = 1; i < N + M; i++) {
        kids[p[i]].pb(i);
    }
}

int count_ways(int L, int R)
{
    for (int i = L; i <= R; i++) {
        a[i - N] ^= 1;
        dp[i][0] ^= 1;
        dp[i][1] ^= 1;
    }

    recalculate(0);

    return dp[0][1];
}