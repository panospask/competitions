#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> dist;
vector<vector<int>> adj_list;
vector<int> p;

void dfs(int node, int par)
{
    dist[node] = dist[par] + 1;
    p[node] = par;

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dfs(neigh, node);
        }
    }
}

int find_max(vector<int>& v, bool pos)
{
    int mpos = -1;
    int mans = -1;

    for (int i = 0; i < v.size(); i++) {
        if (v[i] > mans) {
            mpos = i;
            mans = v[i];
        }
    }

    if (pos) {
        return mpos;
    }
    else {
        return mans;
    }
}

bool test_center(int center, int leaf)
{
    // Root tree at center
    dist[center] = -1;
    dfs(center, center);
    int diameter = dist[leaf] * 2;

    int quarter = leaf;
    while (dist[quarter] != diameter / 4) {
        quarter = p[quarter];
    }

    vector<int> s;
    for (int i = 0; i < N; i++) {
        if (dist[i] == dist[leaf]) {
            s.pb(i);
        }
    }

    while (s.size() > 1) {
        for (int i = 0; i < s.size(); i++) {
            s[i] = p[s[i]];
        }

        int sz = s.size();
        while (sz > 1 && s[sz - 1] == s[sz - 2]) {
            s.pop_back();
            sz--;
        }
    }

    if (dist[s.front()] >= dist[quarter]) {
        // Super special case can be implemented
        diameter--;
        int len = diameter / 2 + 1;
        printf("%d\n", len);
        for (int d = 1; d < len; d++) {
            printf("%d %d\n", center + 1, d);
        }
        printf("%d %d\n", quarter + 1, dist[quarter]);
        return true;
    }

    return false;
}

void solve(void)
{
    scanf("%d", &N);

    adj_list.assign(N, vector<int>(0));
    dist.resize(N);
    p.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dist[0] = -1;
    dfs(0, 0);

    int n1 = find_max(dist, true);
    dist[n1] = -1;
    dfs(n1, n1);
    int diameter = find_max(dist, false); 
    int n2 = find_max(dist, true);

    int center = n2;
    diameter++;
    while (dist[center] != diameter / 2) {
        center = p[center];
    }

    if (diameter % 2) {
        // Normal proceidure
        int len = diameter / 2 + 1;
        printf("%d\n", len);

        for (int d = 0; d < len; d++) {
            printf("%d %d\n", center + 1, d);
        }
    }
    else {
        // Whooho special case
        // Find the quarter point between center and n1
        int c1 = center;
        int c2 = p[center];

        int len = 0;
        for (int i = 1; i <= diameter / 2; i += 2) {
            len++;
        }
        printf("%d\n", 2 * len);
        for (int i = 1; i <= diameter / 2; i += 2) {
            printf("%d %d\n%d %d\n", c1 + 1, i, c2 + 1, i);
        }
    }


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