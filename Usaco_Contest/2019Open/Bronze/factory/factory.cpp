#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int n;
vector<int> adj_list[MAXN];
bool visited[MAXN];
int unvisited;

void dfs(int i)
{
    visited[i] = true;
    unvisited--;

    for (auto neigh : adj_list[i])
        if (!visited[neigh]) {
            dfs(neigh);
        }
}

bool can_reach_all(int i)
{
    memset(visited, false, sizeof(visited));
    unvisited = n;

    dfs(i);

    if (unvisited == 0)
        return true;
    else
        return false;
}

int main(void)
{
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);

    scanf("%d", &n);
    int n1, n2;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &n1, &n2);
        adj_list[--n2].pb(--n1);
    }

    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (can_reach_all(i)) {
            ans = i + 1;
            break;
        }
    }

    printf("%d\n", ans);
    return 0;
}