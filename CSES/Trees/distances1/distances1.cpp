#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

vector<int> adj_list[MAXN + 2];
int n;

int first_path[MAXN + 2]; // Longest path from a node to one of its leaves
int second_path[MAXN + 2]; // Second longest path from a node to one of its leaves
int included_in[MAXN + 2]; // Kid of node that firstleaf path passes from
int p[MAXN + 2];
int maxpar[MAXN + 2];
int maximum[MAXN + 2];

int longest_path[MAXN + 2];

void dfs(int node, int parent)
{
    p[node] = parent;
    first_path[node] = 0;
    second_path[node] = 0;

    for (auto child : adj_list[node])
        if (child != parent) {
            dfs(child, node);
            if (first_path[node] < first_path[child] + 1) {
                second_path[node] = first_path[node];
                first_path[node] = first_path[child] + 1;
                included_in[node] = child;
            }
            else if (second_path[node] < first_path[child] + 1) {
                second_path[node] = first_path[child] + 1;
            }
        }
}

void dfs_par(int node, int root)
{
    // Find the longest path passing through p[node]
    if (node == root) {
        ;
    }
    else if (included_in[p[node]] == node) {
        if (second_path[p[node]] + 1 >= first_path[node]) {
            first_path[node] = second_path[p[node]] + 1;
            included_in[node] = -1;
        }
        else if (second_path[p[node]] + 1 >= second_path[node])
            second_path[node] = second_path[p[node]] + 1;
    }
    else {
        first_path[node] = first_path[p[node]] + 1;
        included_in[node] = -1;
    }

    for (auto child : adj_list[node])
        if (child != p[node])
            dfs_par(child, node);
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
    dfs(0, -1);
    dfs_par(0, 0);

    for (int i = 0; i < n; i++)
        printf("%d ", first_path[i]);
    printf("\n");

    return 0;
}