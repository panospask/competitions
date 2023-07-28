#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int A, B;
vector<vector<int>> dp;

int main(void)
{
    scanf("%d %d", &A, &B);

    dp.resize(A + 1, vector<int>(B + 1, INF));
    for (int i = 1; i <= min(A, B); i++)
        dp[i][i] = 0;

    for (int i = 1; i <= A; i++)
        for (int j = 1; j <= B; j++) {
            // Cut in the i coordinate
            for (int c = 1; c < i; c++) {
                dp[i][j] = min(dp[i][j], dp[c][j] + dp[i -c][j] + 1);
            }
            // Cut in the j coordinate
            for (int c = 1; c < j; c++) {
                dp[i][j] = min(dp[i][j], dp[i][c] + dp[i][j - c] + 1);
            }
        }

    printf("%d\n", dp[A][B]);
    return 0;
}