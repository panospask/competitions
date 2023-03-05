#include <bits/stdc++.h>
#define MAXN 1000
#define MAXM 1000

using namespace std;

char grid[MAXN + 5][MAXM + 5];
bool visited[MAXN + 5][MAXN + 5];

// Changes for moving in S, W, N, E
int dir_hor[4] = {1, 0, -1, 0};
int dir_ver[4] = {0, -1, 0, 1};
int n, m;
int roomcount;

void dfs(int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= m)
        return;
    if (grid[i][j] == '#' || visited[i][j])
        return;

    visited[i][j] = true;
    for (int x = 0; x < 4; x++)
        dfs(i + dir_ver[x], j + dir_hor[x]);
    
    return;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < m; j++)
            grid[i][j] = getchar();
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                roomcount++;
            }
        }

    printf("%d\n", roomcount);
    return 0;
}