#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

typedef pair<int, int> ii;

vector<int> adj_list[MAXN + 2];
int d[MAXN + 2];
int opt[MAXN + 2];
int n, m;

void calc_dist(int root)
{
    for (int i = 0; i < n; i++)
        d[i] = INT_MAX;

    d[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (auto neigh : adj_list[node]) {
            if (d[neigh] > d[node] + 1) {
                d[neigh] = d[node] + 1;
                q.push(neigh);
            }
        }
    }
}

int calc_min_dist(int node) 
{
    if (opt[node] != -1)
        return opt[node];

    int ans = d[node];
    for (auto neigh : adj_list[node]) {
        if (d[neigh] <= d[node]) {
            // We are expending our move, and we won't be able to make further advances from j
            // It would then be optimal to stay at j
            ans = min(ans, d[neigh]);
        }
        else {
            // We have yet to use our move
            ans = min(ans, calc_min_dist(neigh));
        }
    }

    opt[node] = ans;
    return opt[node];
}

void solve(void)
{
    scanf("%d %d", &n, &m);
    memset(d, INT_MAX, sizeof(d));
    memset(opt, -1, sizeof(opt));
    for (int i = 0; i < n; i++) {
        adj_list[i].clear();
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
    }

    calc_dist(0);

    for (int i = 0; i < n; i++) {
        printf("%d ", calc_min_dist(i));
    }
    printf("\n");

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }

    return 0;
}