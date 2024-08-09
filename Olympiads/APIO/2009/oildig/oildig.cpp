#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int ans = 0;
vector<vector<int>> grid;
vector<vector<int>> sums;

// Sum of the oil reserves in the square with top left corner (i1, j1)
int tot(int i1, int j1)
{
    int i2 = i1 + K;
    int j2 = j1 + K;
    if (i1 < 0 || j1 < 0 || i2 > N || j2 > M) {
        return 0;
    }

    return sums[i2][j2] - sums[i2][j1] - sums[i1][j2] + sums[i1][j1];
}

void compute_sums(void)
{
    sums.assign(N + 1, vector<int>(M + 1, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            sums[i + 1][j + 1] = sums[i + 1][j] + sums[i][j + 1] - sums[i][j] + grid[i][j];
        }
    }
}

void calculate(void)
{
    compute_sums();

    vector<int> colmax(M, 0);
    for (int j = 0; j < M; j++) {
        colmax[j] = 0;
        for (int i = 0; i < N; i++) {
            colmax[j] = max(colmax[j], tot(i, j));
        }
    }

    vector<int> colpref(M, 0);
    colpref[0] = colmax[0];
    for (int j = 1; j < M; j++) {
        colpref[j] = max(colpref[j - 1], colmax[j]);
    }

    vector<int> rowmax(N, 0);
    vector<int> rowpref(N, 0);
    vector<int> rowsuff(N, 0);

    int prv_max = 0;

    for (int c = N - 1; c - K > 0; c--) {
        // c is the first column after the splitting line

        if (c + K < M) {
            prv_max = max(prv_max, colmax[c + K]);
        }

        for (int r = 0; r < N; r++) {
            rowmax[r] = max(rowmax[r], tot(r, c));
        }

        rowpref[0] = rowmax[0];
        for (int r = 1; r < N; r++) {
            rowpref[r] = max(rowpref[r - 1], rowmax[r]);
        }
        rowsuff[N - 1] = rowsuff[N - 1];
        for (int r = N - 2; r >= 0; r--) {
            rowsuff[r] = max(rowsuff[r + 1], rowmax[r]);
        }

        for (int r = 0; r < N; r++) {
            int v1 = colpref[c - K];
            int v2 = tot(r, c);
            int v3 = prv_max;
            if (r + K < N) {
                v3 = max(v3, rowsuff[r + K]);
            }
            if (r - K >= 0) {
                v3 = max(v3, rowpref[r - K]);
            }

            ans = max(ans, v1 + v2 + v3);
        }
    }
}

void inverse(void) 
{
    for (int i = 0; i < N; i++) {
        reverse(grid[i].begin(), grid[i].end());
    }
}

void read_input(void)
{
    scanf("%d %d %d", &N, &M, &K);

    grid.resize(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
}

int main(void)
{
    read_input();

    calculate();

    inverse();
    calculate();
    inverse();

    // Now swap rows and columns
    vector<vector<int>> new_grid(M, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            new_grid[j][i] = grid[i][j];
        }
    }

    swap(new_grid, grid);
    swap(N, M);

    calculate();

    inverse();
    calculate();
    inverse();

    printf("%d\n", ans);

    return 0;
}