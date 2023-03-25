#include <bits/stdc++.h>
#define MAXM 200000
#define MAXN 100000
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, pair<bool, int>> ib;
typedef pair<int, int> ii;

vector<int> adj_list[MAXN + 2];
int n, m;
int visited[MAXN + 2];
int outcount[MAXN + 2];
int timer = 1; 
vector<ii> ans;

void dfs(int node, int parent)
{
    if (visited[node])
        return;

    visited[node] = timer++;
    for (auto neigh : adj_list[node]) {
        if (neigh == parent) continue;

        if (visited[neigh]) {
            if (visited[neigh] < visited[node]) {
                // Current node is the child
                ans.pb(mp(node, neigh));
                outcount[node]++;
            }
        }
        else {
            dfs(neigh, node);
            if (outcount[neigh] % 2) { 
                outcount[neigh]++;
                ans.pb(mp(neigh, node));
            }
            else {
                outcount[node]++;
                ans.pb(mp(node, neigh));
            }
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);

    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    bool isgood = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            // Find a dfs tree with root at i
            // Try to make the tree have even outedge
            dfs(i, -1);

            isgood &= outcount[i] % 2 == 0;
        }
    }

    if (isgood) {
        for (auto& p : ans) {
            printf("%d %d\n", p.first + 1, p.second + 1);
        }
    }
    else 
        printf("IMPOSSIBLE\n");
}