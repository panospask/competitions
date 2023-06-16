#include <bits/stdc++.h>

using namespace std;

int N, R, Q;
int cutoff = 0;
vector<int> heavy_regions;
vector<bool> isheavy;
vector<int> home;
vector<int> ancestor_count;
vector<vector<int>> kids;
vector<vector<int>> total_subordinates;
vector<vector<int>> tin_by_region;
vector<vector<int>> id_by_region;

int counter = 0;
vector<int> tin;
vector<int> tout;

void dfs(int node)
{
    tin[node] = counter++;

    int r = home[node];
    tin_by_region[r].push_back(tin[node]);

    for (int i = 0; i < heavy_regions.size(); i++) {
        int curheavy = heavy_regions[i];

        total_subordinates[i][r] += ancestor_count[curheavy];
    }

    ancestor_count[r]++;
    for (auto kid : kids[node])
        dfs(kid);
    ancestor_count[r]--;

    tout[node] = counter;
}

int main(void)
{
    scanf("%d %d %d", &N, &R, &Q);

    cutoff = sqrt(N);

    kids.resize(N);
    home.resize(N);
    tin.resize(N);
    isheavy.resize(R);
    tout.resize(N);
    tin_by_region.resize(R);
    id_by_region.resize(R);

    scanf("%d", &home[0]);
    home[0]--;
    id_by_region[home[0]].push_back(0);
    for (int i = 1; i < N; i++) {
        int p, h;
        scanf("%d %d", &p, &h);
        p--; h--;

        kids[p].push_back(i);
        home[i] = h;
        id_by_region[h].push_back(i);
    }
    for (int i = 0; i < R; i++) {
        if (id_by_region[i].size() > cutoff) {
            isheavy[i] = true;
            heavy_regions.push_back(i);
        }
    }

    ancestor_count.resize(R);
    total_subordinates.resize(heavy_regions.size(), vector<int>(N));
    dfs(0);

    while (Q--) {
        int r1, r2;
        scanf("%d %d", &r1, &r2);
        r1--; r2--;

        int ans = 0;
        if (isheavy[r1]) {
            int pos = lower_bound(heavy_regions.begin(), heavy_regions.end(), r1) - heavy_regions.begin();

            ans = total_subordinates[pos][r2];
        }
        else {
            for (auto i : id_by_region[r1])
                ans += lower_bound(tin_by_region[r2].begin(), tin_by_region[r2].end(), tout[i])
                - lower_bound(tin_by_region[r2].begin(), tin_by_region[r2].end(), tin[i]);
        }

        printf("%d\n", ans);
        fflush(stdout);
    }

    return 0;
}
