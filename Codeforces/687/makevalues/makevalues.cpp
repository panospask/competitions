#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> c;

// dp[i][s1][s2]: True if we can select coins from the first i with sum s1 and special subset with sum s2 
vector<vector<vector<bool>>> dp;

int main(void)
{
    scanf("%d %d", &N, &K);

    c.resize(N);
    dp.resize(N + 1, vector<vector<bool>>(K + 1, vector<bool>(K + 1, false)));

    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }

    dp[0][0][0] = true;
    for (int i = 0; i < N; i++) {
        for (int s1 = 0; s1 <= K; s1++) {
            for (int s2 = 0; s2 <= s1; s2++) {
                if (!dp[i][s1][s2]) {
                    continue;
                }

                // You may not use c[i] at all
                dp[i + 1][s1][s2] = true;

                if (s1 + c[i] <= K) {
                    // Either add c[i] to special subset or dont
                    dp[i + 1][s1 + c[i]][s2] = true;
                    dp[i + 1][s1 + c[i]][s2 + c[i]] = true;
                }
            }
        }
    }

    vector<int> ans;
    for (int s2 = 0; s2 <= K; s2++) {
        if (dp[N][K][s2]) {
            ans.push_back(s2);
        }
    }

    printf("%d\n", (int)ans.size());
    for (auto v : ans) {
        printf("%d ", v);
    }
    printf("\n");
}