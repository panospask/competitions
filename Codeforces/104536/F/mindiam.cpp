#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, M;
vector<vector<int>> adj_list;
vector<int> dist;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dist[neigh] = dist[node] + 1;
            dfs(neigh, node);
        }
    }
}

int find_max(vector<int>& v, bool pos)
{
    int maxval = -1;
    int maxpos = -1;

    for (int i = 0; i < v.size(); i++) {
        if (v[i] > maxval) {
            maxval = v[i];
            maxpos = i;
        }
    }

    if (pos) {
        return maxpos;
    }
    else {
        return maxval;
    }
}

int calculate_diameter(void)
{
    dist[0] = 0;
    dfs(0, -1);

    int furthest = find_max(dist, true);
    dist[furthest] = 0;
    dfs(furthest, -1);

    return find_max(dist, false);
}

void read(int T)
{
    dist.assign(T, -1);
    adj_list.assign(T, vector<int>());

    for (int i = 0; i < T - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
}

int main(void)
{
    scanf("%d", &N);
    read(N);
    int d1 = calculate_diameter();
    scanf("%d", &M);
    read(M);
    int d2 = calculate_diameter();

    int ans = (d1 + 1) / 2 + (d2 + 1) / 2 + 1;
    ans = max(ans, d1);
    ans = max(ans, d2);
    printf("%d\n", ans);
}