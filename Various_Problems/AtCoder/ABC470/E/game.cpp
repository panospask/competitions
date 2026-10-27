#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int N, L;
vector<int> A;
// dp[i][j][k]: Probability of having seen the first i, create j pairs, have remaining life of k
vector<vector<vector<ld>>> dp;

int main(void) {
    scanf("%d %d", &N, &L);

    A.resize(N);
    dp.resize(2 * N + 1, vector<vector<ld>>(N + 1, vector<ld>(L + 1, 0)));
    
    int sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sum += A[i];
    }

    ld ans = 0;
    dp[0][0][L] = 1;
    for (int i = 0; i < 2 * N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = L; k > 0; k--) {
                if (dp[i][j][k] < LDBL_EPSILON) {
                    continue;
                }

                int solo = i - 2 * j;
                if (solo < 0) {
                    continue;
                }
                // Total cards s.t. both cards of a pair are unseen
                int rest = 2 * N - 2 * j - 2 * solo;
                if (rest < 0) {
                    // Impossible
                    continue;
                }

                // We must first choose an "unopened" card
                
                // Case 1: We pick a solo card
                ld p1 = (ld)solo / (rest + solo);
                dp[i + 1][j + 1][k] += p1 * dp[i][j][k];

                if (rest == 0) {
                    continue;
                }
                // Case 2: We pick one of the rest => Forced to pick a second random card
                
                // Subcase 2.1: This card complements the card picked before
                ld p21 = (ld)1 / (rest + solo - 1);
                dp[i + 2][j + 1][k] += (1 - p1) * p21 * dp[i][j][k];

                // Subcase 2.2: This card complements a previous solo card
                ld p22 = (ld)solo / (rest + solo - 1);
                if (k > 1) {
                    dp[i + 2][j + 1][k - 1] += (1 - p1) * p22 * dp[i][j][k];
                }
                else {
                    // We lose because gaining +1 is not an option
                    dp[i + 2][j][k - 1] += (1 - p1) * p22 * dp[i][j][k];
                }

                // Subcase 2.3: This card doesn't complement any previous
                dp[i + 2][j][k - 1] += (1 - p1) * (1 - p21 - p22) * dp[i][j][k];
            }
        }
    }

    for (int j = 0; j <= N; j++) {
        for (int k = 0; k <= L; k++) {
            if (j == N || k == 0) {
                for (int i = 0; i <= 2 * N; i++) {
                    ans += ((dp[i][j][k] * j) / N) * sum;
                }
            }
        }
    }

    cout << fixed << setprecision(8) << ans << endl;
}