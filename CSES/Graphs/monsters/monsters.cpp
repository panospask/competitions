#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int DIRS = 4;

int n, m;
int d_v[] = {1, 0, -1, 0};
int d_h[] = {0, 1, 0, -1};
char d_s[] = {'D', 'R', 'U', 'L'};

vector<vector<char>> grid;
vector<vector<int>> monsterdist;
vector<vector<int>> playerdist;
queue<pi> proc_monster;
pi playerspot;

vector<char> path;

bool solve_player(int i, int j, int pdist)
{
    if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] == '#')
        return false;
    if (playerdist[i][j] != 1e7)
        return false;
    playerdist[i][j] = pdist;
    if (monsterdist[i][j] <= playerdist[i][j])
        return false;


    // If it is a boundary square, return true
    if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
        return true;

    for (int x = 0; x < DIRS; x++) {
        if (solve_player(i + d_v[x], j + d_h[x], playerdist[i][j] + 1)) {
            path.push_back(d_s[x]);
            return true;
        }
    }

    return false;
}

void monster_bfs(void)
{
    while (!proc_monster.empty()) {
        int i, j;
        tie(i, j) = proc_monster.front();
        proc_monster.pop();

        for (int x = 0; x < DIRS; x++) {
            if (i + d_v[x] >= 0 && i + d_v[x] < n && j + d_h[x] >= 0 && j + d_h[x] < m) {
                int ni, nj;
                ni = i + d_v[x];
                nj = j + d_h[x];

                if (grid[ni][nj] != '#' && monsterdist[ni][nj] == 1e7) {
                    monsterdist[ni][nj] = monsterdist[i][j] + 1;
                    proc_monster.push(mp(ni, nj));
                }
            }
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);
    grid.resize(n, vector<char>(m));
    monsterdist.resize(n, vector<int>(m));
    playerdist.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        monsterdist[i].assign(m, 1e7);
        playerdist[i].assign(m, 1e7);
        for (int j = 0; j < m; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'M') {
                monsterdist[i][j] = 0;
                proc_monster.push(mp(i,j));
            }
            else if (grid[i][j] == 'A') {
                playerspot = mp(i, j);
            }
        }
    }

    monster_bfs();
    bool ans = solve_player(playerspot.first, playerspot.second, 0);
    if (ans) {
        printf("YES\n%d\n", (int)path.size());
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++)
            putchar(path[i]);

        putchar('\n');
    }
    else
        printf("NO\n");

    return 0;
}