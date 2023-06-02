#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n, m;
vector<vector<int>> adj_list;
vector<bool> on_stack;
vector<bool> visited;
stack<int> cur;
stack<int> ans;

bool dfs(int node)
{
    if (on_stack[node]) {
        while (cur.top() != node) {
            ans.push(cur.top());
            cur.pop();
        }
        ans.push(node);

        return true;
    }
    if (visited[node]) {
        return false;
    }

    on_stack[node] = true;
    visited[node] = true;
    cur.push(node);

    for (auto neigh : adj_list[node]) {
        if (dfs(neigh))
            return true;
    }

    cur.pop();
    on_stack[node] = false;
    return false;
}

int main(void)
{
    scanf("%d %d", &n, &m);

    adj_list.resize(n);
    visited.assign(n, false);
    on_stack.assign(n, false);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
    }

    bool isgood = false;
    for (int i = 0; i < n && !isgood; i++)
        if (!visited[i])
            isgood = dfs(i);

    if (isgood) {
        // Assuming no self loops
        printf("%d\n", (int)ans.size() + 1);
        int f = ans.top();
        while (!ans.empty()) {
            printf("%d ", ans.top() + 1);
            ans.pop();
        }
        printf("%d\n", f + 1);
    }
    else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}