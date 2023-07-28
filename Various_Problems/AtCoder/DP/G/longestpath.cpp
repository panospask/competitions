#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, M;
vector<vector<int>> adj_list;
vector<int> indeg;
vector<int> dp;

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    indeg.resize(N);
    dp.resize(N);

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        indeg[b]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++)
        if (!indeg[i])
            q.push(i);

    int ans = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans = max(ans, dp[v]);

        for (auto u : adj_list[v]) {
            dp[u] = max(dp[u], dp[v] + 1);

            if (--indeg[u] == 0)
                q.push(u);
        }
    }

    printf("%d\n", ans);
}