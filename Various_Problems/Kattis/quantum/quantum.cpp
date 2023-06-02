#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n1, n2, m1, m2;
vector<vector<bool>> dp[2];

void read_and_process(vector<vector<bool>>& dp, int source, int n, int m)
{
    vector<vector<int>> adj_list(n);
    vector<int> indeg(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        indeg[v]++;
    }

    vector<int> t;
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        t.pb(cur);

        for (auto neigh : adj_list[cur]) {
            indeg[neigh]--;
            if (indeg[neigh] == 0)
                q.push(neigh);
        }
    }

    dp.assign(n, vector<bool>(n, false));
    dp[source][0] = true;

    for (int i = 0; i < n; i++) {
        int cur = t[i];

        for (int s = 0; s < n; s++) {
            if (dp[cur][s] == 0)
                continue;

            for (auto neigh : adj_list[cur])
                dp[neigh][s + 1] = true;
        }
    }
}

int main(void)
{
    scanf("%d %d %d %d", &n1, &n2, &m1, &m2);

    read_and_process(dp[0], 0, n1, m1);
    read_and_process(dp[1], 0, n2, m2);

    int q;
    scanf("%d", &q);

    while (q--) {
        int steps;
        scanf("%d", &steps);

        bool ans = false;
        for (int s1 = 0; s1 < n1 && !ans; s1++) {
            int s2 = steps - s1;
            if (s2 >= 0 && s2 < n2)
                ans = ans || (dp[0][n1 - 1][s1] && dp[1][n2 - 1][s2]);
        }

        if (ans)
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}