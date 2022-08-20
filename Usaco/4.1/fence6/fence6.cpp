/*
ID: panos.p1
LANG: C++11
TASK: fence6
*/

#include <bits/stdc++.h>
#define MAXE 105
#define MAXN 205
#define mp make_pair
#define pb push_back

using namespace std;
typedef pair<int, int> ii;

int vertex[MAXE + 5][MAXE + 5];
vector<ii> adj_list[MAXN];
int curnum = 0;
int e, n;
int neigh[8];
int dist[MAXN];
int par[MAXN];
int ans = INT_MAX;
bool used[MAXN];

int find_min_dist(void)
{
    int mini = -1, mindist = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (dist[i] < mindist && !used[i]) {
            mindist = dist[i];
            mini = i;
        }
    }

    return mini;
}


int shortest_to_self(int i)
{
    memset(used, false, sizeof(used));
    for (int i = 0; i < n; i++)
        dist[i] = 10e7;
    
    for (auto neigh : adj_list[i]) {
        dist[neigh.first] = neigh.second;
        par[neigh.first] = i;
    }

    int cur;
    while (true) {
        cur = find_min_dist();
        if (cur == i) break;
        if (cur == -1 || dist[cur] == 10e7) break;
        
        for (auto neigh : adj_list[cur]) {
            if (neigh.first != par[cur]) {
                if (used[neigh.first]) 
                    dist[i] = min(dist[i], dist[neigh.first] + dist[cur] + neigh.second);
                else if (dist[neigh.first] > dist[cur] + neigh.second) {
                    dist[neigh.first] = dist[cur] + neigh.second;
                    par[neigh.first] = cur;
                }
            }
        }

        used[cur] = true;
    }

    return dist[i];
}

int main(void)
{
    freopen("fence6.in", "r", stdin);
    freopen("fence6.out", "w", stdout);

    scanf("%d", &e);
    for (int i = 0; i <= e; i++)
        for (int j = 0; j <= e; j++)
            vertex[i][j] = -1;
    int length, num, n1, n2;
    int curseg1;
    int curseg2;
    for (int i = 1; i <= e; i++) {
        scanf("%d %d %d %d", &num, &length, &n1, &n2);

        // First line
        curseg1 = -1;
        for (int j = 0; j < n1; j++) {
            scanf("%d", &neigh[j]);
            if (vertex[num][neigh[j]] != -1)
                curseg1 = vertex[num][neigh[j]];
        }
        if (curseg1 == -1)
            curseg1 = curnum++;
        for (int j = 0; j < n1; j++) {
            vertex[num][neigh[j]] = curseg1;
            vertex[neigh[j]][num] = curseg1;
        }

        // Second line
        curseg2 = -1;
        for (int j = 0; j < n2; j++) {
            scanf("%d", &neigh[j]);
            if (vertex[num][neigh[j]] != -1)
                curseg2 = vertex[num][neigh[j]];
        }
        if (curseg2 == -1)
            curseg2 = curnum++;
        for (int j = 0; j < n2; j++) {
            vertex[num][neigh[j]] = curseg2;
            vertex[neigh[j]][num] = curseg2;
        }

        // UNITE!!!
        adj_list[curseg1].pb(mp(curseg2, length));
        adj_list[curseg2].pb(mp(curseg1, length));
    }
    n = curnum;

    // Find shortest perimeter(path to oneself)
    for (int i = 0; i < n; i++)
        ans = min(ans, shortest_to_self(i));

    printf("%d\n", ans);
    return 0;
}