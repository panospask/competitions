#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;

int N;
vector<bool> smaller;
// dp[i][j]: # of ways to create a permutation using the first i signs and j as last element
vector<vector<int>> dp;
vector<vector<int>> pref;

int main(void)
{
    scanf("%d", &N);

    smaller.resize(N);
    for (int i = 1; i <= N - 1; i++) {
        char c;
        scanf(" %c", &c);
        smaller[i] = c == '<';
    }

    dp.resize(N + 1, vector<int>(N + 1));
    pref.resize(N + 1, vector<int>(N + 1));
    pref[0].assign(N + 1, 1);
    dp[0][0] = 1;

    for (int i = 1; i < N; i++) {
        pref[i - 1][i] = pref[i - 1][i - 1];
        for (int j = 0; j <= i; j++) {
            dp[i][j] = 0;
            if (smaller[i]) {
                // Count all smaller than i
                if (j)
                    dp[i][j] = pref[i -1][j - 1];
            }
            else {
                // Count all larger than i
                dp[i][j] = pref[i - 1][i];
                if (j)
                    dp[i][j] -= pref[i - 1][j - 1];

                if (dp[i][j] < 0)
                    dp[i][j] += MOD;
            }

            pref[i][j] = dp[i][j];
            if (j)
                pref[i][j] += pref[i][j - 1];

            if (pref[i][j] > MOD)
                pref[i][j] -= MOD;
        }
    }

    int ans = 0;
    for (int i = 0; i <= N - 1; i++) {
        ans += dp[N - 1][i];
        if (ans  > MOD)
            ans -= MOD;
    }
    printf("%d\n", ans);
}