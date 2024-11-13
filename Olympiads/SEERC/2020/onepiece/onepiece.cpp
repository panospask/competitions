#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;
vector<bool> good;

vector<int> dist;

vector<int> p;

vector<int> tot;

void dfs(int node, int par, int d)
{
    if (d < 0) {
        good[node] = false;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dfs(neigh, node, d - 1);
        }
    }
}

bool probabsort(int i, int j)
{
    if (good[i] == good[j]) {
        if (p[i] == p[j]) {
            return i < j;
        }
        return p[i] < p[j];
    }
    return good[i];
}

void process(int node, int par, int d)
{
    if (!good[node]) {
        return;
    }

    if (d == 0) {
        tot.pb(node);
        return;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            process(neigh, node, d - 1);
        }
    }
}

void probability_calculate(int s)
{
    tot.clear();

    process(s, -1, dist[s]);

    for (int i = 0; i < tot.size(); i++) {
        p[tot[i]] = tot.size();
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    good.assign(N, true);
    dist.resize(N);
    p.assign(N, N + 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        
        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    int minv = N;
    int mini = -1;

    for (int i = 0; i < N; i++) {
        scanf("%d", &dist[i]);

        if (dist[i] < minv) {
            minv = dist[i];
            mini = i;
        }
    }

    int a = mini, b = -1;

    dfs(a, -1, dist[a]);
    for (auto v : adj_list[a]) {
        if (dist[v] == dist[a]) {
            b = v;
            dfs(b, -1, dist[b]);
            break;
        }
    }

    probability_calculate(a);
    if (b != -1) {
        probability_calculate(b);
    }

    vector<int> ans;
    for (int i = 0; i < N; i++) {
        ans.pb(i);
    }

    sort(ans.begin(), ans.end(), probabsort);

    for (auto v : ans) {
        printf("%d ", v + 1);
    }
    printf("\n");

    return 0;
}