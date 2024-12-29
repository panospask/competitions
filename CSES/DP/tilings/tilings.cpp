#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << pos))

using namespace std;

const int MOD = 1e9 + 7;

int N, M;

// dp[i][mask]: Number of ways to cover the first i columns of the grid (0 to i-1)
// such that the positions marked in mask are taken in column i
vector<vector<int>> dp;

// propagate[i][mask][j]: Number of ways to cover the first i columns of the grind (0 to i-1)
// such that AT MOST the positions marked in mask are taken in column i.
// j denotes the first positioin from which we can make two consecutive spots(starting at j) in marked into one 1x2 tile
// i is left out of the dimensions since we can process each i seperately
vector<vector<int>> propagate;

void add(int& a, int b)
{
    a += b;
    if (a > MOD) {
        a -= MOD;
    }
}

int NOT(int m)
{
    return (1 << N) - m - 1;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    dp.assign(M + 1, vector<int>(1 << N, 0));
    dp[0][0] = 1;

    for (int i = 0; i < M; i++) {
        propagate.assign(1 << N, vector<int>(N + 1, 0));
        
        for (int mask = 0; mask < (1 << N); mask++) {
            add(propagate[NOT(mask)][0], dp[i][mask]);
        }

        // Iterate backwards and propagate the result
        for (int mask = (1 << N) - 1; mask >= 0; mask--) {
            for (int j = 0; j < N; j++) {
                add(propagate[mask][j + 1], propagate[mask][j]);

                if (CHECK_BIT(mask, j) && CHECK_BIT(mask, j + 1)) {
                    // Create a new 1x2 tile
                    int new_mask = mask - (1 << j) - (1 << (j + 1));
                    add(propagate[new_mask][j + 2], propagate[mask][j]);
                }
            }

            dp[i + 1][mask] = propagate[mask][N];
        }
    }

    printf("%d\n", dp[M][0]);
}