#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 500

using namespace std;

vector<int> adj_list[MAXN + 5];
bool visited[MAXN + 5];
int ans[MAXN + 5];
int lastans;
int n;

bool dfs(int node, int start)
{
    if (visited[node]) {
        if (node == start)
            return true;
        else 
            return false;
    }

    visited[node] = true;
    bool can_make = false;
    for (auto neigh : adj_list[node]) {
        if (dfs(neigh, start)) {
            can_make = true;
            lastans = neigh;
            break;
        }
    }

    return can_make;
}


int main(void)
{
    // freopen("redistribute.in", "r", stdin);
    // freopen("redistribute.out", "w", stdout);

    scanf("%d", &n);
    int gift;
    for (int i = 0; i < n; i++) { 
        bool bef = true;
        for (int j = 0; j < n; j++) {
            scanf("%d", &gift);
            gift--;
            if (bef && gift != i)
                adj_list[i].pb(gift);
            else 
                bef = false;
        }
    }

    for (int i = 0; i < n; i++) {
        memset(visited, false, sizeof(visited));
        if (dfs(i, i))
            ans[i] = lastans;
        else
            ans[i] = i;
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", ans[i] + 1);
    return 0;
}