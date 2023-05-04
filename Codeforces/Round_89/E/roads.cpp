#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int n, m;
vector<vector<int>> adj_list;
vector<int> idx;
vector<int> low;
vector<pi> edges;
int counter = 0;

bool find_bridges(int node, int par = -1)
{
    idx[node] = low[node] = counter++;
    for (auto kid : adj_list[node]) {
        if (idx[kid] == -1) {

            if (!find_bridges(kid, node))
                return false;

            if (low[kid] > idx[node]) {
                return false;
            }
            low[node] = min(low[node], low[kid]);
            edges.push_back(make_pair(node, kid));
        }
        else {
            if (kid != par && idx[kid] < idx[node]) {
                low[node] = min(low[node], idx[kid]);
                edges.push_back(make_pair(node, kid));
            }
        }
    }

    return true;
}

int main() {
    scanf("%d %d", &n, &m);
    adj_list.resize(n);
    idx.assign(n, -1);
    low.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d",  &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    bool ans = find_bridges(0);
    if (ans) {
        for (auto e : edges)
            printf("%d %d\n", e.first + 1, e.second + 1);
    }
    else {
        printf("0\n");
    }

    return 0;
}