#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

const int LETTERS = 26;

int n, m;
int ans = 0;
string s;
vector<vector<int>> adj_list;
vector<vector<int>> dp;

vector<int> toposort;
vector<bool> on_stack;
vector<bool> visited;

bool dfs(int node)
{
    if (on_stack[node])
        return false;
    if (visited[node])
        return true;

    visited[node] = true;
    on_stack[node] = true;

    for (auto neigh : adj_list[node])
        if (!dfs(neigh))
            return false;

    toposort.pb(node);
    on_stack[node] = false;
    return true;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    adj_list.resize(n);

    cin >> s;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
    }

    visited.assign(n, false);
    on_stack.assign(n, false);
    bool isgood = true;
    for (int i = 0; i < n && isgood; i++)
        if (!visited[i])
            isgood = dfs(i);

    if (!isgood) {
        printf("-1\n");
        return 0;
    }

    reverse(toposort.begin(), toposort.end());

    dp.assign(n, vector<int>(LETTERS, 0));
    for (int i = 0; i < n; i++) {
        int cur = toposort[i];

        dp[cur][s[cur] - 'a']++;
        for (int let = 0; let < LETTERS; let++) {
            if (dp[cur][let] == 0)
                continue;
            ans = max(ans, dp[cur][let]);

            for (auto neigh : adj_list[cur])
                dp[neigh][let] = max(dp[neigh][let], dp[cur][let]);
        }
    }

    printf("%d\n", ans);
    return 0;
}