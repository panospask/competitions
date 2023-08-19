#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
string S;

vector<vector<int>> dp;

int main(void)
{
    cin >> S;
    N = S.size();

    int cur_sum = 0;
    int target_sum = 0;

    int M = 0;
    for (int i = 0; i < N; i++)
        if (S[i] - '0') {
            M++;
            cur_sum += i + 1;
        }

    target_sum = 2 * N * M - N * N +N * (N + 1) / 2 - M * (M - 1) / 2 + (N - M) * (N - M - 1) / 2;
    target_sum /= 2;

    int ans = 0;

    dp.assign(M + 1, vector<int>(target_sum + 1, 1e9));
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = M; j > 0; j--)
            for (int k = target_sum; k > i; k--) {
                // Add current position (either swap or don't)
                dp[j][k] = min(dp[j][k], dp[j - 1][k - i - 1] + (S[i] == '0'));
            }
    }

    printf("%d\n", dp[M][target_sum]);
}