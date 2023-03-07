#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

vector<int> adj_list[MAXN + 2];
int n;
int dist[MAXN + 2];

int find_min_for_child_spread(int node, int parent)
{
    int children = adj_list[node].size();
    if (parent != -1)
        children--;

    if (children == 0)
        return 0;

    int infected_cows = 1;
    int time = 0;
    while (infected_cows < children + 1) {
        infected_cows *= 2;
        time++;
    }

    for (auto child : adj_list[node])
        if (child != parent)
            time += find_min_for_child_spread(child, node) + 1;

    return time;
}

int main(void)
{
    // freopen("cowntagion.in", "r", stdin);
    // freopen("cowntagion.out", "w", stdout);

    scanf("%d", &n);
    
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    printf("%d\n", find_min_for_child_spread(0, -1));
    return 0;
}