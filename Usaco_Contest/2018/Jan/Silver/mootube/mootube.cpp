#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 5000

using namespace std;

typedef pair<int, int> ii;

int n, q;
vector<ii> adj_list[MAXN + 2];
int dist[MAXN + 2][MAXN + 2];

void dfs(int node, int parent, int root)
{
    for (auto neigh : adj_list[node]) {
        if (neigh.first != parent) {
            dist[root][neigh.first] = min(dist[root][node], neigh.second);
            dfs(neigh.first, node, root);
        }
    }
}

int main(void)
{
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    scanf("%d %d", &n, &q);
    int a, b, r;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d %d", &a, &b, &r);
        a--; b--;

        adj_list[a].pb(mp(b,r));
        adj_list[b].pb(mp(a,r));
    }

    for (int i = 0; i < n; i++) {
        dist[i][i] = INT_MAX;
        dfs(i,-1,i);
    }

    for (int x = 0; x < q; x++) {
        int vid, rel;
        scanf("%d %d", &rel, &vid);
        vid--;

        int ans = 0;
        for (int i = 0; i < n; i++)
            if (dist[vid][i] >= rel && vid != i)
                ans++;

        printf("%d\n", ans);
    }

    return 0;
}