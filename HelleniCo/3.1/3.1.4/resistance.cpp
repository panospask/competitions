#include <bits/stdc++.h>

using namespace std;

struct island {
    int vertex1;
    int vertex2;
    int weight;
};
typedef struct island Island;

int roots[200005], height[200005], n, m, b, total_trees;
vector<Island> edges;

bool my_func(Island a, Island b)
{
    if (a.weight < b.weight)
        return true;
    
    return false;
}

void init(void)
{
    total_trees = n;
    for (int i = 1; i <= n; i++) {
        roots[i] = i;
        height[i] = 0;
    }
}

int find_root(int x)
{
    if (roots[x] != x)
        roots[x] = find_root(roots[x]);
    
    return roots[x];
}

void join_trees(int x, int y)
{
    int root1 = find_root(x);
    int root2 = find_root(y);

    if (height[root1] > height[root2]) 
        roots[root2] = root1;
    else if (height[root1] < height[root2])
        roots[root1] = root2;
    else {
        roots[root2] = root1;
        height[root1]++;
    }

    total_trees--;
}

bool same_root(int x, int y)
{
    if (find_root(x) == find_root(y))
        return true;
    
    return false;
}

int main(void)
{
    freopen("resistance.in", "r", stdin);
    freopen("resistance.out", "w", stdout);

    cin >> n >> m >> b;

    init();
    edges.resize(m);
    bool using_edge[m];
    memset(using_edge, false, sizeof(using_edge));

    Island read_isl;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &read_isl.vertex1, &read_isl.vertex2, &read_isl.weight);

        if (read_isl.vertex1 > read_isl.vertex2)
            swap(read_isl.vertex1, read_isl.vertex2);
        
        edges[i] = read_isl;
    }

    sort(edges.begin(), edges.end(), my_func);

    int cur_edge = m - 1;
    Island cur_is;
    while (cur_edge >= 0 && total_trees > 1) {
        cur_is = edges[cur_edge];
        if (!same_root(cur_is.vertex1, cur_is.vertex2)) {
            join_trees(cur_is.vertex1, cur_is.vertex2);
            using_edge[cur_edge] = true;
        }

        cur_edge--;
    }

    int destroyed = 0;
    for (int i = 0; i < m; i++) {
        if (b >= edges[i].weight) {
            if (!using_edge[i]) {
                destroyed++;
                b -= edges[i].weight;
            }
        }
        else 
            break;
    }

    cout << destroyed << '\n';
}