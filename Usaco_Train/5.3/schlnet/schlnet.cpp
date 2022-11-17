/*
ID: panos.p1
LANG: C++11
TASK: schlnet
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

vector<int> adj_list[MAXN];
vector<int> rev_list[MAXN];
int n;

bool reachable[MAXN];
bool visited[MAXN];
set<int> dominating;
set<int> codominating;
vector<int> reach_from_src;

void dfs(int node, bool direction)
{
    visited[node] = true;
    reach_from_src.pb(node);

    vector<int> lst = (direction ? adj_list[node] : rev_list[node]);
    for (auto neigh : lst) {
        if (!visited[neigh])
            dfs(neigh, direction);
    }
}

int main(void)
{
    freopen("schlnet.in", "r", stdin);
    freopen("schlnet.out", "w", stdout);

    scanf("%d", &n);
    int neigh;
    for (int i = 0; i < n; i++) {
        scanf("%d", &neigh);
        while (neigh != 0) {
            neigh--;
            adj_list[i].pb(neigh);
            rev_list[neigh].pb(i);
            scanf("%d", &neigh);
        }
    }

    memset(reachable, false, sizeof(reachable));
    for (int i = 0; i < n; i++) 
        if (!reachable[i]) {
            reach_from_src.clear();
            memset(visited, false, sizeof(visited));
            dfs(i, true);
            for (auto reached : reach_from_src) {
                reachable[reached] = true;
                dominating.erase(reached);
            }
            dominating.insert(i);
        }
    printf("%d\n", (int) dominating.size());

    bool strong_connect = true;
    if (dominating.size() != 1)
        strong_connect = false;
    for (int i = 0; i < n && strong_connect; i++) {
        memset(visited, false, sizeof(visited));
        reach_from_src.clear();
        dfs(i, true);
        if (reach_from_src.size() != n)
            strong_connect = false;
    }

    memset(reachable, false, sizeof(reachable));
    for (int i = 0; i < n && !strong_connect; i++) 
        if (!reachable[i]) {
            reach_from_src.clear();
            memset(visited, false, sizeof(visited));
            dfs(i, false);
            for (auto reached : reach_from_src) {
                reachable[reached] = true;
                codominating.erase(reached);
            }
            codominating.insert(i);
        }

    if (strong_connect)
        printf("%d\n", 0);
    else 
        printf("%d\n", (int) max(dominating.size(), codominating.size()));

    return 0;
}