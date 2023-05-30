#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back


using namespace std;

typedef pair<int, int> pi;

int n, m, l;
vector<set<int>> adj_list;
vector<vector<int>> accessible_regions;

map<pi, int> edgeholder;
vector<int> members;
vector<vector<int>> crosses;

void check_edge(int i, int j, int region)
{
    if (edgeholder.find(mp(i, j)) != edgeholder.end()) {
        int r2 = edgeholder[mp(i, j)];
        adj_list[r2].insert(region);
        adj_list[region].insert(r2);
    }
    else {
        edgeholder[mp(j, i)] = region;
        edgeholder[mp(i, j)] = region;
    }
}

void calculate_distance(vector<int>& sources, vector<int>& dist)
{
    dist.assign(m, INT_MAX);

    queue<int> q;
    for (auto s : sources) {
        dist[s] = 0;
        q.push(s);
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto neigh : adj_list[cur])
            if (dist[neigh] > dist[cur] + 1) {
                dist[neigh] = dist[cur] + 1;
                q.push(neigh);
            }
    }
}

int main(void)
{
    scanf("%d %d %d", &m, &n, &l);
    adj_list.resize(m);
    accessible_regions.resize(n + 1);
    members.resize(l);
    crosses.resize(l);

    for (int i = 0; i < l; i++) {
        scanf("%d", &members[i]);
    }

    for (int r = 0; r < m; r++) {
        int towns;
        scanf("%d", &towns);

        vector<int> curt(towns);
        for (int t = 0; t < towns; t++) {
            scanf("%d", &curt[t]);
            accessible_regions[curt[t]].pb(r);
        }
        if (r == m - 1)
            reverse(curt.begin(), curt.end());

        for (int i = 1; i < towns; i++)
            check_edge(curt[i - 1], curt[i], r);

        check_edge(curt.back(), curt.front(), r);
    }

    for (int i = 0; i < l; i++) {
        calculate_distance(accessible_regions[members[i]], crosses[i]);
    }

    int ans = INT_MAX;
    int ansregion = -1;
    for (int r = 0; r < m; r++) {
        // Check region r
        int crosssum = 0;
        for (int i = 0; i < l; i++)
            crosssum += crosses[i][r];

        if (crosssum < ans) {
            ans = crosssum;
            ansregion = r;
        }
    }

    printf("%d\n%d\n", ans, ansregion + 1);
    return 0;
}