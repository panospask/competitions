#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = (int)1e9 + 7;

int N, K;
vector<int> a;

// dp[c][i] : How many ways are there such as candy i is the last candy that children with ID c and below receive
vector<vector<int>> dp;
// line prefix sums of dp
vector<vector<int>> pref;

int main(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N + 1);
    dp.resize(N + 1, vector<int>(K + 1));
    pref.resize(N + 1, vector<int>(K + 1));

    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }

    dp[0].assign(K + 1, 0);
    dp[0][0] = 1;
    pref[0].assign(K + 1, 1);
    for (int c = 1; c <= N; c++) {
        for (int i = 0; i <= K; i++) {
            // Child c can receive from 0 up to a[c] candies
            ll p = pref[c - 1][i];

            int pos = i - a[c] - 1;
            if (pos >= 0)
                p -= pref[c - 1][pos];

            if (p < 0)
                p += MOD;
            dp[c][i] = p;
        }
        pref[c][0] = dp[c][0];
        for (int i = 1; i <= K; i++) {
            pref[c][i] = pref[c][i - 1] + dp[c][i];
            if (pref[c][i] > MOD)
                pref[c][i] -= MOD;
        }
    }

    printf("%d\n", dp[N][K]);
}