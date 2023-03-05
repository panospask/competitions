#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 250

using namespace std;

typedef pair<int, int> ii;

int u = 0, l = 1, d = 2, r = 3;
int dir_ver[4] = {-1, 0, 1, 0};
int dir_hor[4] = {0, -1, 0, 1};
int n;
int id[MAXN + 5][MAXN + 5];
bool visited[MAXN + 5][MAXN + 5];
int component_size[MAXN * MAXN];
int cur_comp = 0;
int belongs_to[MAXN + 5][MAXN + 5];
vector<int> adj_list[MAXN * MAXN];
int colour[MAXN * MAXN];
bool visited_component[MAXN * MAXN];
map<ii, bool> connected;
map<ii, bool> checked_comp_w_colour;

int accept;
int cur_vis;

int dfs(int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
        return 0;
    if (visited[i][j] || (id[i][j] != accept)) {
        if (visited[i][j] && id[i][j] != accept && !connected.count(mp(cur_comp, belongs_to[i][j]))) {
            adj_list[cur_comp].pb(belongs_to[i][j]);
            adj_list[belongs_to[i][j]].pb(cur_comp);
        }
        return 0;
    }

    visited[i][j] = true;
    belongs_to[i][j] = cur_comp;
    cur_vis++;
    for (int x = 0; x < 4; x++)
        dfs(i + dir_ver[x], j + dir_hor[x]);
    
    return 0;
}

int dfs(int comp, int col1, int col2)
{
    if (colour[comp] != col1 && colour[comp] != col2)
        return 0;
    if (visited_component[comp])
        return 0;
    
    if (colour[comp] == col1)
        checked_comp_w_colour[mp(comp, col2)] = true;
    else 
        checked_comp_w_colour[mp(comp, col1)] = true;

    visited_component[comp] = true;
    int cur_size = component_size[comp];
    for (auto& neigh : adj_list[comp])
        cur_size += dfs(neigh, col1, col2);

    return cur_size;
}

int main(void)
{
    freopen("multimoo.in", "r", stdin);
    freopen("multimoo.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &id[i][j]);
    
    int singlemax = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!visited[i][j]) {
                accept = id[i][j];
                dfs(i, j);
                singlemax = max(singlemax, (int)cur_vis);
                component_size[cur_comp] = cur_vis;

                colour[cur_comp] = id[i][j];
                cur_vis = 0;
                cur_comp++;
            }

    int doublemax = 0;
    int component_size = cur_comp;
    for (int i = 0; i < cur_comp; i++) {
        // Find max using cur_comp
        for (auto& j : adj_list[i]) {
            if (j < i) continue;
            if (checked_comp_w_colour.count(mp(i, colour[j]))) continue;
            memset(visited_component, false, sizeof(visited_component));
            int res =  dfs(i, colour[i], colour[j]);
            if (res > doublemax)
                doublemax = res;
        }
    }

    printf("%d\n%d\n", singlemax, doublemax);
    return 0;
}