#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

int nodecount[MAXN + 2]; // Total number of nodes in the subtree with root i
long long int subtree_dist[MAXN + 2]; // Total distance from all nodes of a subtree to the root
int p[MAXN + 2]; // Parent of node i in the adrbitrary rooted tree

long long int total_dist[MAXN + 2];

int n;
vector<int> adj_list[MAXN + 2];

void dfs(int node, int parent)
{
    p[node] = parent;

    nodecount[node] = 1;
    subtree_dist[node] = 0;
    for (auto child : adj_list[node]) {
        if (child != parent) {
            dfs(child, node);
            nodecount[node] += nodecount[child];
            subtree_dist[node] += subtree_dist[child] + nodecount[child];
        }
    }
}

void calc_ttl_dist(int node, int root)
{
    if (node == root)
        total_dist[node] = subtree_dist[node];
    else {
        total_dist[node] = subtree_dist[node];
        
        int nodes_from_parent = n - nodecount[node];
        long long int parent_dist = total_dist[p[node]] - subtree_dist[node] - nodecount[node];

        total_dist[node] += parent_dist + nodes_from_parent; 
    }

    for (auto neigh : adj_list[node])
        if (neigh != p[node])
            calc_ttl_dist(neigh, root);
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

    // Arbitrarily root the tree at 0
    dfs(0,-1);
    calc_ttl_dist(0,0);

    for (int i = 0; i < n; i++)
        printf("%lld ", total_dist[i]);
    printf("\n");

    return 0;
}