#include <bits/stdc++.h>

using namespace std;

int n, m;

// dp1[i]: Is the number of ways that i is black and connected to all black nodes in its subtree
vector<long long> dp1;

// What if you took only the first (or last) i kids of the node
vector<vector<long long>> pref_dp1;
vector<vector<long long>> suff_dp1;

// dp2[i]: Number of ways to paint the parent of i black(or white and everything else too) if we exclude the subtree of i
vector<long long> dp2;
vector<set<int>> adj_list;
vector<vector<int>> actual_list;
vector<int> p;

void init_dfs(int node, int par, int rank)
{
    adj_list[node].erase(par);
    actual_list[node].resize(adj_list[node].size());

    suff_dp1[node].resize(adj_list[node].size() + 2);
    pref_dp1[node].resize(adj_list[node].size() + 2);

    dp1[node] = 1;
    int pos = 1;
    pref_dp1[node][0] = 1;
    for (auto kid : adj_list[node]) {
        init_dfs(kid, node, pos);
        dp1[node] = (dp1[node] * (dp1[kid] + 1)) % m;
        pref_dp1[node][pos] = dp1[kid] + 1;
        suff_dp1[node][pos] = dp1[kid] + 1;
        actual_list[node][pos-1] = kid;
        pos++;
    }
    suff_dp1[node][pos] = 1;

    for (int i = 1; i < pos; i++)
        pref_dp1[node][i] = pref_dp1[node][i] * pref_dp1[node][i - 1] % m;
    for (int i = pos - 1; i > 0; i--)
        suff_dp1[node][i] = suff_dp1[node][i] * suff_dp1[node][i + 1] % m;
}

void dfs2(int node)
{
    int pos = adj_list[node].size() + 1;
    for (int i = 1; i < pos; i++)
        dp2[actual_list[node][i-1]] = 1 + ((pref_dp1[node][i-1] * suff_dp1[node][i+1]) % m) * dp2[node] % m;

    for (auto kid : adj_list[node])
        dfs2(kid);
}

int main(void)
{
    scanf("%d %d", &n, &m);
    adj_list.resize(n);
    p.resize(n);
    dp1.resize(n);
    dp2.resize(n);
    actual_list.resize(n);
    suff_dp1.resize(n);
    pref_dp1.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].insert(b);
        adj_list[b].insert(a);
    }

    init_dfs(0, -1, 1);
    dp2[0] = 1;
    dfs2(0);

    for (int i = 0; i < n; i++) {
        long long ans = dp1[i] * dp2[i] % m;
        printf("%lld\n", ans);
    }

    return 0;
}