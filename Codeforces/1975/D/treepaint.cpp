#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;
vector<int> d1, d2;
vector<int> lpath;
vector<int> a_dist;
int ans = INT_MAX;
int A, B;

void dfs(int node, int par, vector<int>& d)
{
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            d[neigh] = d[node] + 1;
            dfs(neigh, node, d);
        }
    }
}

void clear(void)
{
    a_dist.clear();
    lpath.clear();
    d1.clear();
    d2.clear();
    adj_list.clear();
}

bool calculate_answer(int node, int par)
{
    bool good = false;
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            good = good || calculate_answer(neigh, node);
        }
    }
    if (B == node) {
        good = true;
    }

    if (!good) {
        return false;
    }

    int arrival_time;
    if (a_dist[node] < a_dist[B] - a_dist[node]) {
        arrival_time = a_dist[B] - a_dist[node];
    }
    else {
        arrival_time = a_dist[node];
        if (a_dist[node] % 2 != (a_dist[B] - a_dist[node]) % 2) {
            arrival_time++;
        }
    }

    ans = min(ans, arrival_time + 2 * (N - 1) - lpath[node]);

    return true;
}

void solve(void)
{
    clear();

    scanf("%d", &N);

    ans = INT_MAX;
    d1.assign(N, 0);
    d2.assign(N, 0);
    lpath.assign(N, 0);
    a_dist.assign(N, 0);
    adj_list.resize(N);

    scanf("%d %d", &A, &B);
    A--; B--;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    int end1 = 0, end2 = 0;

    dfs(A, -1, a_dist);
    for (int i = 0; i < N; i++) {
        if (a_dist[end1] < a_dist[i]) {
            end1 = i;
        }
    }
    dfs(end1, -1, d1);
    for (int i = 0; i < N; i++) {
        if (d1[end2] < d1[i]) {
            end2 = i;
        }
    }
    dfs(end2, -1, d2);

    for (int i = 0; i < N; i++) {
        lpath[i] = max(d1[i], d2[i]);
    }

    calculate_answer(A, -1);

    printf("%d\n", ans);
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