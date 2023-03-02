#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

int n;
char grid[MAXN + 5][MAXN + 5];
bool visited[MAXN + 5][MAXN + 5];
int cur_area;
int cur_per;

void dfs(int i, int j)
{
    if (visited[i][j])
        return;

    visited[i][j] = true;
    cur_area++;
    if (i != 0 && grid[i-1][j] == '#') 
        dfs(i-1, j);
    else
        cur_per++;
    
    if (i != n-1 && grid[i+1][j] == '#')
        dfs(i+1, j);
    else 
        cur_per++;
    
    if (j != 0 && grid[i][j-1] == '#')
        dfs(i, j-1);
    else 
        cur_per++;
    
    if (j != n-1 && grid[i][j+1] == '#')
        dfs(i, j+1);
    else
        cur_per++;

    return;
}

int main(void)
{
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < n; j++)
            grid[i][j] = getchar();
    }

    int max_area = 0;
    int max_per = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid[i][j] == '#' && !visited[i][j]) {
                cur_area = 0;
                cur_per = 0;
                dfs(i, j);
                if (cur_area > max_area) {
                    max_area = cur_area;
                    max_per = cur_per;
                }
                else if (cur_area == max_area && cur_per < max_per) {
                    max_area = cur_area;
                    max_per = cur_per;
                }
            }

    printf("%d %d\n", max_area, max_per);
    return 0;
}