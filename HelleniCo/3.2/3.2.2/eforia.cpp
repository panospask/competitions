#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<pair<int,int>> adj_list[1000001];
int num_of_edges[1000001];
vector<int> odd_edges;
bool visited[1000001] = {false};
long long int dist_from_a[1000001] = {0};

bool my_func(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b)
{
    if (a.first > b.first)
        return true;
    
    return false;
}

long long int shortest_path(int a, int b)
{
    set<pair<int,int>> q;
    set<pair<int,int>>::iterator it;

    dist_from_a[a] = 0;
    pair<int,pair<int,int>> cur_edge;
    for (int i = 1; i <= n; i++) {
        dist_from_a[i] = LONG_LONG_MAX;
    }
    dist_from_a[a] = 0;

    q.insert(make_pair(0,a));
    pair<int,int> cur_node;

    while(!q.empty()) {
        cur_node = *(q.begin()); q.erase(cur_node);
        if (cur_node.second == b)
            return cur_node.first;
        for (auto neigh : adj_list[cur_node.second]) {
            if (dist_from_a[neigh.first] > dist_from_a[cur_node.second] + neigh.second) {
                q.erase(make_pair(dist_from_a[neigh.first], neigh.first));
                dist_from_a[neigh.first] = dist_from_a[cur_node.second] + neigh.second;
                q.insert(make_pair(dist_from_a[neigh.first], neigh.first));
            }
        }
    }

    return -1;
}

int main(void)
{
    freopen("eforia.in", "r", stdin);
    freopen("eforia.out", "w", stdout);

    cin >> n >> m;

    long long int result = 0;

    int ver1, ver2, weight;
    pair<int,int> p;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &ver1, &ver2, &weight);
        p.first = ver2;
        p.second = weight;
        adj_list[ver1].push_back(p);
        p.first = ver1;
        adj_list[ver2].push_back(p);
        num_of_edges[ver1]++;
        num_of_edges[ver2]++;
        result += weight;
    }
    for (int i = 1; i <= n && odd_edges.size() <= 2; i++) {
        if (num_of_edges[i] % 2) {
            odd_edges.push_back(i);
        }
    }

    result += shortest_path(odd_edges[0], odd_edges[1]);

    cout << result << '\n';
    return 0;
}