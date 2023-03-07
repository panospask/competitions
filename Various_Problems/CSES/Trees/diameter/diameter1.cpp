#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

int n;
vector<int> adj_list[MAXN + 2];
int maxleaf[MAXN + 2];
int second_maxleaf[MAXN + 2];

void calc_leaf_dist(int node, int parent)
{
    int leafdist = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh != parent) {
            calc_leaf_dist(neigh, node);
            if (maxleaf[neigh] + 1 >= leafdist) {
                second_maxleaf[node] = leafdist;
                leafdist = maxleaf[neigh] + 1;
            }
            else if (maxleaf[neigh] + 1 > second_maxleaf[node])
                second_maxleaf[node] = maxleaf[neigh] + 1;
        }
    }

    maxleaf[node] = leafdist;
}

int main(void)
{
    scanf("%d", &n);
    
    int a, b;
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    // We set node 0 as arbitrary root
    calc_leaf_dist(0, -1);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        // What if the top point of the diameter is i?

        ans = max(ans, maxleaf[i] + second_maxleaf[i]);
    }

    printf("%d\n", ans);
    return 0;
}