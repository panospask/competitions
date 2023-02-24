#include <bits/stdc++.h>
#define MAXN 100000
#define MAXM 100000

using namespace std;

typedef pair<int, int> ii;

vector<ii> adj_list[MAXN + 5];
vector<int> costs;
bool visited[MAXN + 5];
int n, m, d;
vector<int> curpath;
vector<int> dist;
vector<int> par;

bool can_reach(int maxcost)
{
    memset(visited, false, sizeof(visited));
    queue<int> nodes_to_proc;
    dist.clear();
    dist.resize(n);
    par.resize(n);
    nodes_to_proc.push(0);
    visited[0] = true;
    dist[0] = 0;
    par[0] = 0;
    bool found = false;
    while (!nodes_to_proc.empty()) {
        int cur = nodes_to_proc.front();
        nodes_to_proc.pop();
        if (dist[cur] > d) break;
        if (cur == n - 1) {found = true; break;}

        for (auto neigh : adj_list[cur]) {
            if (!visited[neigh.first] && neigh.second <= maxcost) {
                visited[neigh.first] = true;
                dist[neigh.first] = dist[cur] + 1;
                par[neigh.first] = cur;
                nodes_to_proc.push(neigh.first);
            }
        }
    }

    return found;
}

int main(void)
{
    scanf("%d %d %d", &n, &m, &d);
    int n1, n2, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &n1, &n2, &c);
        adj_list[--n1].push_back(make_pair(--n2, c));
        costs.push_back(c);
    }   
    sort(costs.begin(), costs.end());


    int l = -1; // can_reach(costs[l]) = false
    int r = m; // can_reach(costs[r]) = true
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_reach(costs[mid]))
            r = mid;
        else 
            l = mid;
    }

    int ans;
    if (r == m) {
        printf("-1\n");
    }
    else {
        curpath.clear();
        memset(visited, false, sizeof(visited));
        can_reach(costs[r]);
        for (int i = n - 1; i != 0; i = par[i])
            curpath.push_back(i);
        curpath.push_back(0);
        reverse(curpath.begin(), curpath.end());
        printf("%d\n", (int)curpath.size() - 1);
        for (auto vertex : curpath)
            printf("%d ", vertex + 1);
    }
    return 0;
}