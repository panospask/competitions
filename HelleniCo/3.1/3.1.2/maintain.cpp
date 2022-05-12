#include <bits/stdc++.h>

using namespace std;

multiset<pair<int,pair<int,int>>> edges;
int roots[205], height[205], n, m, total_trees;

void init(void) 
{
    for (int i = 1; i <= n; i++) {
        roots[i] = i;
        height[i] = 0;
    }

    total_trees = n;
}

int find_root(int a)
{
    if (roots[a] != a)
        roots[a] = find_root(roots[a]);
    
    return roots[a];
}

bool same_root(int a, int b)
{
    if (find_root(a) == find_root(b))
        return true;
    
    return false;
}

void join_trees(int a, int b)
{
    int root1 = find_root(a);
    int root2 = find_root(b);

    if (height[root1] > height[root2])
        roots[root2] = root1;
    else {
        roots[root1] = root2;
        if (height[root1] == height[root2])
            height[root2]++;
    }

    total_trees--;
}

long long int mst(void)
{
    init();
    long long int total_weight = 0;

    for (auto edge : edges) {
        if (total_trees == 1)
            break;

        if (!same_root(edge.second.first, edge.second.second)) {
            join_trees(edge.second.first, edge.second.second);
            total_weight += edge.first;
        }
    }

    if (total_trees == 1)
        return total_weight;
    
    return -1;
}

int main(void)
{
    freopen("maintain.in", "r", stdin);
    freopen("maintain.out", "w", stdout);

    cin >> n >> m;

    pair<int, pair<int, int>> edge;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edge.second.first, &edge.second.second, &edge.first);
        edges.insert(edge);

        printf("%lld\n", mst());
    }
}