#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 3000

using namespace std;

vector<int> adj_list[MAXN + 5];
int n, m;
int cur_vis;
bool visited[MAXN + 5];
bool closed[MAXN + 5];
int cur_closed = 0;
int closeorder[MAXN + 5];
int firstopen = 0;

void dfs(int node)
{
    if (visited[node] || closed[node])
        return;

    visited[node] = true;
    cur_vis++;
    for (auto neigh : adj_list[node])
        dfs(neigh);
}

int main(void)
{
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        closeorder[i+1] = --a;
    }
    closeorder[0] = -1; // Close no barn to start with
    cur_closed = 0;
    for (int i = 0; i < n; i++) {
        if (i != 0) {
            cur_closed++;
            closed[closeorder[i]] = true;
            while (closed[firstopen]) firstopen++;
        }

        cur_vis = 0;
        memset(visited, false, sizeof(visited));
        dfs(firstopen);
        if (cur_vis == n - cur_closed)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}