#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int n, m;
vector<vector<int>> adj_list;
vector<bool> visited;
vector<bool> used;
vector<ii> ans;

bool dfs(int node, int target, int parent)
{
    if (visited[node]) {
        if (node != target)
            return false;
        else {
            return true;
        }
    }

    visited[node] = true;
    // Prioritise finding the target
    if (target != parent) {
        int findcheck = lower_bound(adj_list[node].begin(), adj_list[node].end(), target) - adj_list[node].begin();
        if (findcheck < adj_list[node].size() && adj_list[node][findcheck] == target) {
            ans.push_back(make_pair(target, node));
            used[target] = true;
            return true;
        }
    }

    for (auto neigh : adj_list[node]) {
        if (neigh != parent) {
            if (dfs(neigh, target, node)) {
                ans.push_back(make_pair(neigh, node));
                used[neigh] = true;
                return true;
            }
        }
    }

    return false;
}

void solve(void)
{
    scanf("%d %d", &n, &m);
    ans.clear();
    adj_list.clear();
    adj_list.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }
    for (int i = 0; i < n; i++)
        sort(adj_list[i].begin(), adj_list[i].end());

    bool isgood = false;
    for (int i = 0; i < n && !isgood; i++) {
        visited.assign(n, false);
        used.assign(n, false);
        if (adj_list[i].size() >= 4 && dfs(i, i, -1)) {
            int cnt = 0;
            isgood = true;
            for (auto n : adj_list[i]) {
                if (!used[n]) {
                    ans.push_back(make_pair(i, n));
                    cnt++;
                }
                if (cnt == 2)
                    break;
            }
        }
    }

    if (!isgood)
        printf("NO\n");
    else {
        printf("YES\n");
        printf("%d\n", (int)ans.size());
        for (auto e : ans)
            printf("%d %d\n", e.first + 1, e.second + 1);
    }

    return;
}

int t;
int main(void)
{
    scanf("%d", &t);
    while (t--)
        solve();
}