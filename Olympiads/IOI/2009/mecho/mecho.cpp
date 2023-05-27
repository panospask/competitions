#include <bits/stdc++.h>

#define f first
#define s second
#define mp make_pair

using namespace std;

const int DIRS = 4;
const int d_v[] = {1, 0, -1, 0};
const int d_h[] = {0, 1, 0, -1};

typedef pair<int, int> pi;

int n, steps;
vector<pi> hives;
vector<vector<char>> grid;
vector<vector<int>> bee_distance;
vector<vector<int>> dist;
vector<vector<bool>> vis;
pi dest, mecho;

bool inbound(int coord)
{
    return coord >= 0 && coord < n;
}

void calculate_distance(vector<pi>& sources, vector<vector<int>>& dist, bool ismecho, int stepcycle)
{
    queue<pi> q;
    dist.resize(n);
    for (int i = 0; i < n; i++)
        dist[i].assign(n, 1e9);

    for (int i = 0; i < sources.size(); i++) {
        dist[sources[i].f][sources[i].s] = 0;
        q.push(sources[i]);
    }

    while(!q.empty()) {
        int i, j;
        tie(i, j) = q.front(); q.pop();

        for (int x = 0; x < DIRS; x++) {
            int ni = i + d_v[x];
            int nj = j + d_h[x];
            if (inbound(ni) && inbound(nj)
                && (grid[ni][nj] == 'G' || grid[ni][nj] == 'M' || (ismecho && grid[ni][nj] == 'D'))
                && dist[ni][nj] == 1e9) {

                dist[ni][nj] = dist[i][j] + stepcycle;
                q.push(mp(ni, nj));
            }
        }
    }
}

bool solve_mecho(pi m, int curtime)
{
    queue<pi> q;
    q.push(m);

    dist = bee_distance;
    vis.assign(n, vector<bool>(n, false));
    if (dist[m.f][m.s] <= curtime)
        return false;

    dist[m.f][m.s] = curtime;

    while (!q.empty()) {
        int i, j;
        tie(i, j) = q.front(); q.pop();

        if (i == dest.f && j == dest.s)
            return true;

        for (int x = 0; x < 4; x++) {
            int ni = i + d_v[x];
            int nj = j + d_h[x];

            if (inbound(ni) && inbound(nj)
                && dist[ni][nj] > dist[i][j] + 1
                && (grid[ni][nj] == 'G' || grid[ni][nj] == 'D')
                && !vis[ni][nj]) {
                    vis[ni][nj] = true;
                    dist[ni][nj] = dist[i][j] + 1;
                    q.push(mp(ni, nj));
                }
        }
    }

    return false;
}

bool can_reach(int x)
{
    return solve_mecho(mecho, x * steps);
}

int main(void)
{
    scanf("%d %d", &n, &steps);

    grid.resize(n, vector<char>(n));
    bee_distance.assign(n, vector<int>(n, 1e9));
    vis.assign(n, vector<bool>(n, false));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'H')
                hives.push_back(mp(i, j));
            else if (grid[i][j] == 'D')
                dest = mp(i, j);
            else if (grid[i][j] == 'M')
                mecho = mp(i, j);
        }

    calculate_distance(hives, bee_distance, false, steps);

    int l = -1;
    int r = 1;

    while(can_reach(r)) {
        l = r;
        r *= 2;
    }
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_reach(mid))
            l = mid;
        else
            r = mid;
    }

    int ans = l;
    printf("%d\n", ans);

    return 0;
}