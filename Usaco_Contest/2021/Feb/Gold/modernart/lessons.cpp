#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int N;
vector<int> A;
vector<vector<int>> dp;

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    dp.assign(N, vector<int>(N, INF));

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int len = 1; len <= N; len++) {
        for (int l = 0; l + len - 1 < N; l++) {
            int r = l + len - 1;
            if (len == 1) {
                // Base case
                dp[l][r] = 1;
                continue; 
            }

            for (int i = l; i < r; i++) {
                dp[l][r] = min(dp[l][r], dp[l][i] + dp[i + 1][r]);
            }
            if (A[l] == A[r]) {
                dp[l][r] += -1;
            }
        }
    }

    printf("%d\n", dp[0][N - 1]);
}