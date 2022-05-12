#include <bits/stdc++.h>  
  
using namespace std;  
  
vector<pair<int,int>> adj_list[10000];  
int incoming_edges[10000] = {0};  
int min_time[10000];  
long long int max_time[10000];  
vector<int> max_vec[10000];  
int n, m;  
  
void init(void)  
{  
    for (int i = 0; i < n; i++) {  
        max_time[i] = -1;  
        min_time[i] = INT_MAX;
    }  
    incoming_edges[0] = 1;  
}  
  
void bfs(void)  
{  
    long long int time_diff = 0;  
    pair<vector<int>,long long int> teams;  
    queue<pair<vector<int>,long long int>> q;  
  
    teams.first.push_back(0);    
    teams.second = 0;
    min_time[0] = 0;  
    q.push(teams);  
    int cur_ver;  
  
    while(!q.empty())   
    {  
        teams = q.front(); q.pop();  
        cur_ver = teams.first.back();  
        incoming_edges[cur_ver]--;  
        if (max_time[cur_ver] < teams.second) {  
            max_time[cur_ver] = teams.second;  
            max_vec[cur_ver] = teams.first;  
        }  
        if (min_time[cur_ver] > teams.second) {  
            min_time[cur_ver] = teams.second;    
        }  
        if (incoming_edges[cur_ver] == 0) {  
            time_diff += max_time[cur_ver] - min_time[cur_ver];  
            for (auto node : adj_list[cur_ver]) {  
                teams.first = max_vec[cur_ver];  
                teams.first.push_back(node.first);  
                teams.second = max_time[cur_ver] + node.second;  
                q.push(teams);  
            }  
        }  
    }  
  
    printf("%lld %lld %ld\n", max_time[n - 1], time_diff, n - max_vec[n - 1].size());  
}  
  
int main(void)  
{  
    freopen("troodos.in", "r", stdin);  
    freopen("troodos.out", "w", stdout);  
  
    cin >> n >> m;  
    pair<int,int> edge;  
    int vec1, vec2, weight;  
    for (int i = 0; i < m; i++) {  
        scanf("%d %d %d", &vec1, &vec2, &weight);  
        edge.first = vec2;  
        edge.second = weight;  
        adj_list[vec1].push_back(edge);  
        incoming_edges[vec2]++;  
    }  
  
    init();  
    bfs();  
}