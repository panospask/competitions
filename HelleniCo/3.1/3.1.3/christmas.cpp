#include <bits/stdc++.h>

using namespace std;

struct road {
    int vertex1;
    int vertex2;
    long long int weight;
};
typedef struct road Road;

struct connect {
    int vertex;
    long long int weight;
    int num_in_array;
};
typedef struct connect Connect;

int n, m, roots[50005], height[50005], total_trees;
vector<Road> edges;
vector<Connect> adj_list[50005];
bool used[100000] = {false};
bool visited[50005] = {false};
vector<int> nums_of_roads;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void preprocess();

bool my_func(Road a, Road b)
{
    if (a.weight < b.weight)
        return true;
    
    return false;
}

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

void join_trees(int a, int b)
{
    int root1 = find_root(a);
    int root2 = find_root(b);

    if (height[root1] > height[root2]) 
        roots[root2] = root1;
    else if (height[root2] > height[root1])
        roots[root1] = root2;
    else {
        roots[root2] = root1;
        height[root1]++;
    }
    total_trees--;
}

bool same_root(int a, int b)
{
    if (find_root(a) == find_root(b))
        return true;
    
    return false;
}

bool find_cycle(int node, int father)
{
    vector<Connect> cur_adj = adj_list[node];

    for (auto road : cur_adj) {
        if (used[road.num_in_array]) {
            if (!visited[road.vertex]) {
                visited[road.vertex] = true;
                nums_of_roads.push_back(road.num_in_array);
                if (find_cycle(road.vertex, node))
                    return true;
                visited[road.vertex] = false;
                nums_of_roads.pop_back();
            }
            else if (road.vertex != father) {
                visited[road.vertex] = true;
                nums_of_roads.push_back(road.num_in_array);
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    freopen("christmas.in", "r", stdin);
    freopen("christmas.out", "w", stdout);

    cin >> n >> m;
    init();
    edges.resize(m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &edges[i].vertex1, &edges[i].vertex2, &edges[i].weight);
    }
    sort(edges.begin(), edges.end(), my_func);
    Road cur_edge;

    Road cur_road;
    long long int min_weight = 0;
    for (int i = 0; i < m && total_trees > 1; i++) {
        cur_road = edges[i];
        if (!same_root(cur_road.vertex1, cur_road.vertex2)) {
            join_trees(cur_road.vertex1, cur_road.vertex2);
            used[i] = true;
            min_weight += cur_road.weight;
            Connect cur_connect;
            cur_connect.num_in_array = i;
            cur_connect.weight = cur_road.weight;
            cur_connect.vertex = cur_road.vertex2;
            adj_list[cur_road.vertex1].push_back(cur_connect);
            cur_connect.vertex = cur_road.vertex1;
            adj_list[cur_road.vertex2].push_back(cur_connect);
        }
    }
    
    long long int sec_min_weight = INT_MAX;
    for (int i = 0; i < m; i++) {
        cur_road = edges[i];
        if (!used[i]) {
            memset(visited, false, sizeof(visited));
            visited[cur_road.vertex1] = true;
            visited[cur_road.vertex2] = true;
            find_cycle(cur_road.vertex1, cur_road.vertex2);

            long long int max_x = INT_MIN;
            for (auto x : nums_of_roads) {
                if (edges[x].weight > max_x)
                    max_x = edges[x].weight;
            }

            long long int cur_sum = min_weight + edges[i].weight - max_x;
            if (sec_min_weight > cur_sum)
                sec_min_weight = cur_sum;
        }
    }

    cout << min_weight << ' ' << sec_min_weight << '\n';
}