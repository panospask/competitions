#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj_list;
vector<int> indegree;
int remaining;

queue<int> ans;

int main(void)
{
    scanf("%d %d", &n, &m);
    adj_list.resize(n);
    indegree.assign(n, 0);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;

    for (int v = 0; v < n; v++)
        if (indegree[v] == 0)
            q.push(v);

    remaining = n;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans.push(v);
        remaining--;

        for (auto neigh : adj_list[v]) {
            indegree[neigh]--;
            if (indegree[neigh] == 0)
                q.push(neigh);
        }
    }

    if (!remaining) {
        while (!ans.empty()) {
            printf("%d ", ans.front() + 1);
            ans.pop();
        }
        printf("\n");
    }
    else {
        printf("IMPOSSIBLE\n");
    }

    return 0;
}