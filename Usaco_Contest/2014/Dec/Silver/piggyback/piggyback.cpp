#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int b, e, p, n, m;
vector<vector<int>> adj_list;
vector<int> b_dist;
vector<int> e_dist;
vector<int> dest_dist;

void calc_dist(int source, int step, vector<int>& dist)
{
    dist.assign(n, INT_MAX);

    dist[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto neigh : adj_list[cur])
            if (dist[neigh] > dist[cur] + step) {
                dist[neigh] = dist[cur] + step;
                q.push(neigh);
            }
    }
}

int main(void)
{
    freopen("piggyback.in", "r", stdin);
    freopen("piggyback.out", "w", stdout);

    scanf("%d %d %d %d %d", &b, &e, &p, &n, &m);

    adj_list.resize(n);
    b_dist.resize(n);
    e_dist.resize(n);
    dest_dist.resize(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &v, &u);
        v--; u--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    calc_dist(0, b, b_dist);
    calc_dist(1, e, e_dist);
    calc_dist(n - 1, min(b + e, p), dest_dist);

    int ans = INT_MAX;
    for (int i = 0; i < n; i++)
        ans = min(ans, b_dist[i] + e_dist[i] + dest_dist[i]);

    printf("%d\n", ans);
    return 0;
}