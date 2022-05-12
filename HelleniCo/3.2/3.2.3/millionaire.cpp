#include <bits/stdc++.h>

using namespace std;
vector<pair<int,double>> adj_list[1001];
bool cur_visited[10001] = {false};
bool visited[10001] = {false};

bool dfs(double cur_money, int cur_edge)
{
    if (cur_visited[cur_edge]) {
        if (cur_money > 1) {
            return true;
        }
        else   
            return false;
    }

    cur_visited[cur_edge] = true;
    visited[cur_edge] = true;

    double new_money;
    for (auto node : adj_list[cur_edge]) {
        new_money = cur_money * (0.5 + 1.5 * node.second);
        bool is_good = dfs(new_money, node.first);
        if (is_good)
            return true;
    }

    cur_visited[cur_edge] = false;

    return false;
}

int main(void)
{
    freopen("millionaire.in", "r", stdin);
    freopen("millionaire.out", "w", stdout);

    int n, m, t;
    cin >> t;
    int node1, node2;
    double per;

    for (int x = 0; x < t; x++) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %lf", &node1, &node2, &per);
            per /= 100;
            adj_list[node1].push_back(make_pair(node2, per));
        }


        bool possible = false;
        for (int i = 1; i <= n && !possible; i++) {
            if (!visited[i]) {
                memset(cur_visited, false, sizeof(cur_visited));
                if (dfs(1, i))
                    possible = true;
            }
       }

        if (possible)
            printf("Possible\n");
        else 
            printf("Not possible\n");
    }
}