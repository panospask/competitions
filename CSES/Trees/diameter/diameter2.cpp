#include <bits/stdc++.h>
#define pb push_back
#define MAXN 200000

using namespace std;

vector<int> adj_list[MAXN + 2];
int n;
int furthestnode;
int maxdist;
int dist[MAXN + 2];

int dfs(int node, int parent) {
    if (parent != -1) {
        dist[node] = dist[parent] + 1;
        if (dist[node] > maxdist) {
            furthestnode = node;
            maxdist = dist[node];
        }
    }

    for (auto& child : adj_list[node])
        if (child != parent)
            dfs(child, node);

    return dist[node];
}

int main(void)
{
    scanf("%d", &n);

    int a, b;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    furthestnode = 0;
    dist[0] = 0;
    dfs(0, -1);
    dist[furthestnode] = 0;
    maxdist = 0;
    dfs(furthestnode, -1);

    printf("%d\n", maxdist);
    return 0;
}