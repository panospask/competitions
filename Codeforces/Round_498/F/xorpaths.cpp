#include <bits/stdc++.h>

using namespace std;

int n, m;
long long k;
vector<vector<long long int>> grid;

int main(void)
{
    scanf("%d %d %lld", &n, &m, &k);
    grid.resize(n, vector<long long>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%lld", &grid[i][j]);

    int moves = n + m - 2;

    if (moves == 0) {
        printf("%d\n",(int) (grid[0][0] == k));
        return 0;
    }

    vector<vector<map<long long, int>>> paths_resulting_left(n, vector<map<long long, int>>(m));
    // Manually test all leftpaths
    int leftmoves = moves / 2;
    for (int s = 0; s < (1<<leftmoves); s++) {
        long long xorsum = grid[0][0];
        int r = 0, c = 0;
        bool inside = true;
        for (int i = 0; i < leftmoves; i++) {

            if (s & (1<<i))
                r++;
            else
                c++;

            if (r >= n || c >= m) {
                inside = false;
                break;
            }

            xorsum ^= grid[r][c];
        }

        if (inside)
            paths_resulting_left[r][c][xorsum]++;
    }

    long long ans = 0;
    // Now generate rightpaths
    int rightmoves = moves - leftmoves - 1;
    for (int s = 0; s < (1<<rightmoves); s++) {
        int r = n - 1, c = m - 1;
        long long xorsum = grid[r][c];
        bool inside = true;

        for (int i = 0; i < rightmoves; i++) {
            if (s & (1<<i))
                r--;
            else
                c--;

            if (r < 0 || c < 0) {
                inside = false;
                break;
            }

            xorsum ^= grid[r][c];
        }

        if (inside) {
            // Search for matching left paths
            if (r != 0)
                ans += paths_resulting_left[r-1][c][k ^ xorsum];
            if (c != 0)
                ans += paths_resulting_left[r][c-1][k ^ xorsum];
        }
    }

    printf("%lld\n", ans);
    return 0;
}