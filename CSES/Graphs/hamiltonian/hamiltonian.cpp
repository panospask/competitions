#include <bits/stdc++.h>
#define MAXN 20
#define MAXDP 1048576
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define ADD_BIT(pos) (1 << (pos))
#define MOD ((int)1e9 + 7)

using namespace std;

vector<int> adj_list[MAXN + 2];
long long int dp[MAXDP][MAXN + 2];
int n, m;

int main(void)
{
    scanf("%d %d", &n, &m);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
    }

    dp[1][0] = 1;
    for (int i = 1; i < MAXDP; i++) {
        for (int j = 0; j < n; j++) {
            if (!dp[i][j])
                continue;

            for (auto& neigh : adj_list[j]) {
                if (!CHECK_BIT(i, neigh)) {
                    dp[i + ADD_BIT(neigh)][neigh] += dp[i][j];
                    dp[i + ADD_BIT(neigh)][neigh] %= MOD;
                }
            }
        }
    }

    long long int ans = dp[(1<<n) -1][n-1];

    printf("%lld\n", ans);
    return 0;
}