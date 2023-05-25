#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<vector<int>> adj_list;
vector<vector<long long>> dp;
vector<long long> opt;
vector<int> f;
vector<int> a;

void calc_best_for(int node, int par)
{
    for (auto kid : adj_list[node]) {
        if (kid == par)
            continue;

        calc_best_for(kid, node);
    }

    opt[node] = LONG_LONG_MAX;
    for (int i = 1; i <= n; i++) {

        if (a[node] >= i) {
            dp[i][node] += 1e10;
            continue;
        }

        dp[i][node] = f[i];
        for (auto kid : adj_list[node]) {
            if (kid == par)
                continue;

            ll add = opt[kid];
            if (a[kid] == (a[node] + 1) % i)
                add = min(add, dp[i][kid] - f[i]);

            dp[i][node] += add;
        }

        opt[node] = min(opt[node], dp[i][node]);
    }
}

int main(void)
{
    scanf("%d", &n);
    a.resize(n);
    dp.resize(n + 1, vector<long long>(n));
    opt.resize(n + 1);
    adj_list.resize(n);
    f.resize(n + 1);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i]);

    for (int i = 0; i < n-1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    calc_best_for(0, -1);

    printf("%lld\n", opt[0]);

    return 0;
}