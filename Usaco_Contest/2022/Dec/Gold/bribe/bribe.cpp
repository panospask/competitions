#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int N, A, B;
vector<vector<int>> dp;
vector<vector<int>> prv;
vector<int> p;
vector<int> x;
vector<int> c;

int main(void)
{
    // freopen("bribe.in", "r", stdin);
    // freopen("bribe.out", "w", stdout);

    scanf("%d %d %d", &N, &A, &B);

    p.resize(N);
    x.resize(N);
    c.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d", &p[i], &c[i], &x[i]);
    }

    dp.resize(A + 1, vector<int>(B + 1));
    prv.resize(A + 1, vector<int>(B + 1));
    dp[0][0] = 0;
    for (int cur = 0; cur < N; cur++) {
        for (int i = A; i >= 0; i--)
            for (int j = B; j >= 0; j--) {
                // Contribute normally
                int n_i = i + c[cur];
                int n_j = j;

                while (n_j <= B) {
                    if (n_i <= A && n_i >= i) {
                        dp[n_i][n_j] = max(dp[n_i][n_j], prv[i][j] + p[cur]);
                    }

                    n_j += x[cur];
                    n_i--;
                }
            }

        for (int i = 0; i <= A; i++)
            for (int j = 0; j <= B; j++) {
                if (i) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                }
                if (j) {
                    dp[i][j] = max(dp[i][j], dp[i][j - 1]);
                }
            }

        prv = dp;
    }

    printf("%d\n", dp[A][B]);

    return 0;
}