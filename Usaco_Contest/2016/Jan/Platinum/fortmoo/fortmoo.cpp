#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int n, m;
vector<vector<bool>> grid;
vector<vector<int>> swampy_total;

int main(void)
{
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);

    scanf("%d %d", &n, &m);
    grid.resize(n, vector<bool>(m));
    swampy_total.resize(n+1, vector<int>(m+1));
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < m; j++)
            grid[i][j] = getchar() == 'X';
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            swampy_total[i][j] = swampy_total[i-1][j] + swampy_total[i][j-1] - swampy_total[i-1][j-1] + grid[i-1][j-1];

    int ans = 0;
    for (int c1 = 0; c1 < m; c1++)
        for (int c2 = c1; c2 < m; c2++) {
            // Find the optimal rectange with columns c1, c2
            int prev_row = -1;

            for (int r = 0; r < n; r++) {
                int res = swampy_total[r + 1][c2 + 1] - swampy_total[r][c2 + 1]
                    - swampy_total[r + 1][c1] + swampy_total[r][c1];

                if (res == 0) {
                    ans = max(ans, c2 - c1 + 1);
                    if (prev_row != -1)
                        ans = max(ans, (c2 - c1 + 1) * (r - prev_row + 1));
                }

                if (grid[r][c1] || grid[r][c2]) {
                    // Reset prev
                    prev_row = -1;
                }

                if (res == 0 && prev_row == -1)
                    prev_row = r;
            }
        }

    printf("%d\n", ans);
    return 0;
}