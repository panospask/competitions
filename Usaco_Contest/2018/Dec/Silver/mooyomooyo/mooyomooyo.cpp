#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100
#define JMAX 10

using namespace std;

typedef pair<int, int> ii;

int grid[MAXN + 10][JMAX + 10];
bool visited[MAXN + 10][JMAX + 10];
int n, k;
vector<ii> cur_comp;
int dir_ver[4] = {1, 0, -1, 0};
int dir_hor[4] = {0, 1, 0, -1};

void dfs(int i, int j, int num)
{
    if (i < 0 || i >= n || j < 0 || j >= JMAX)
        return;
    if (grid[i][j] != num || visited[i][j])
        return;

    visited[i][j] = true;
    cur_comp.pb(mp(i,j));

    for (int x = 0; x < 4; x++)
        dfs(i + dir_ver[x], j + dir_hor[x], num);
}

void update_board(void)
{
    for (int j = 0; j < JMAX; j++) {
        // Column by column
        int cur_i_spot = n-1;
        for (int i = n-1; i >= 0; i--) 
            if (grid[i][j] == 0) {
                cur_i_spot = min(cur_i_spot, i);
                while (cur_i_spot >= 0 && grid[cur_i_spot][j] == 0)
                    cur_i_spot--;

                if (cur_i_spot >= 0)
                    swap(grid[i][j], grid[cur_i_spot][j]);
            }
    }
}

void print_grid(void)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < JMAX; j++)
            printf("%d", grid[i][j]);
        printf("\n");
    }
}

int main(void)
{
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < JMAX; j++)
            scanf("%1d", &grid[i][j]);

    bool changes_made = true;
    // print_grid();
    while (changes_made) {
        memset(visited, false, sizeof(visited));
        changes_made = false;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < JMAX; j++)
                if (!visited[i][j] && grid[i][j] != 0) {
                    cur_comp.clear();
                    dfs(i, j, grid[i][j]);
                    if (cur_comp.size() >= k) {
                        for (auto& tile : cur_comp)
                            grid[tile.first][tile.second] = 0;
                        changes_made = true;
                    }
                }

        if (changes_made) {
            update_board();
            // print_grid();
        }
    }

    print_grid();

    return 0;
}