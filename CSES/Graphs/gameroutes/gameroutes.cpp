#include <bits/stdc++.h>
#define MAXN 100000
#define MOD ((int)1e9 + 7)

using namespace std;

int topsort[MAXN + 2];
vector<int> adj_list[MAXN + 2];
bool visited[MAXN + 2];
long long int dp[MAXN + 2];
int spot = 0;
int n, m;

void dfs(int i)
{
    if (visited[i])
        return;

    visited[i] = true;

    for (auto neigh : adj_list[i])
        dfs(neigh);

    topsort[spot++] = i;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
    }

    // Create a topological sorting
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < n; i++)
        dfs(i);
    reverse(topsort, topsort + n);

    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // Begin at level 1

    for (int i = 0; i < n; i++) {
        int curnode = topsort[i];
        for (auto neigh : adj_list[curnode]) {
            dp[neigh] = (dp[curnode] + dp[neigh]) % MOD;
        }
    }

    printf("%lld\n", dp[n-1]);
    return 0;
}
