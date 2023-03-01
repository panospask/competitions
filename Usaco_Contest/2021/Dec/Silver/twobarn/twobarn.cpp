#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

vector<vector<int>> Components;
vector<int> adj_list[MAXN + 5];
bool visited[MAXN + 5];
int comp[MAXN + 5];
int n, m;

void dfs(int node, int rep)
{
    if (visited[node])
        return;
    
    visited[node] = true;
    comp[node] = rep;
    for (auto neigh : adj_list[node])
        dfs(neigh, rep);
}

void calc_dist(int to_calc, int* dist)
{
    for (int i = 0; i < Components.size(); i++)
        dist[i] = INT_MAX;

    int cur_barn_index = 0;
    for (int i = 0; i < n; i++) {
        int curdist = abs(Components[to_calc][cur_barn_index] - i);
        while (cur_barn_index < Components[to_calc].size() - 1 && abs(Components[to_calc][cur_barn_index + 1] - i) < curdist) {
            cur_barn_index++;
            curdist = abs(Components[to_calc][cur_barn_index] - i);
        } 

        dist[comp[i]] = min(dist[comp[i]], curdist);
    }

    return;
}


void solve(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        adj_list[i].clear();

    int a, b;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    memset(visited, 0, sizeof(visited));
    memset(comp, -1, sizeof(comp));
    int compnum = 0;
    for (int i = 0; i < n; i++)
        if (comp[i] == -1) {
            dfs(i, compnum);
            compnum++;
        }

    if (comp[0] == comp[n-1]) {
        printf("0\n");
        return;
    }

    Components.clear();
    Components.resize(compnum);
    // They are sorted since we go from 0 to n-1
    for (int i = 0; i < n; i++)
        Components[comp[i]].pb(i);

    // Find the component containing 0 and calculate all associated distances
    vector<int> firstcomp = Components[comp[0]];
    int firstdist[compnum];
    calc_dist(comp[0], firstdist);
    // And for the component containing n - 1
    vector<int> secondcomp = Components[comp[n-1]];
    int secdist[compnum];
    calc_dist(comp[n-1], secdist);

    long long int min_ttl = LONG_LONG_MAX;
    for (int i = 0; i < compnum; i++) {
        // Go from 0 component to n-1 component using i-th component
        min_ttl = min(min_ttl, (long long int)firstdist[i] * firstdist[i] + (long long int)secdist[i] * secdist[i]);
    }

    printf("%lld\n", min_ttl);
    return;
}

int main(void)
{
    // freopen("twobarn.in", "r", stdin);
    // freopen("twobarn.out", "w", stdout);

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
        solve();
}