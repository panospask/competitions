#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int n, m;
vector<vector<int>> adj_list;
vector<int> indeg;

int main(void)
{
    scanf("%d %d", &n, &m);

    indeg.resize(n);
    adj_list.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        // Reverse the order
        adj_list[b].pb(a);
        indeg[a]++;
    }

    vector<int> topsort;
    priority_queue<int> q;
    for (int i = 0; i < n; i++)
        if (!indeg[i])
            q.push(i);

    while (!q.empty()) {
        int cur = q.top();
        topsort.pb(cur);
        q.pop();

        for (auto neigh : adj_list[cur]) {
            indeg[neigh]--;
            if (!indeg[neigh])
                q.push(neigh);
        }
    }

    reverse(topsort.begin(), topsort.end());
    for (auto node : topsort)
        printf("%d ", node + 1);
    printf("\n");

    return 0;
}