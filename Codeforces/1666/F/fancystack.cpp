#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;
const int MAXV = 5000;

int N;
vector<int> a;

// dp[i][j]: Have processed the i biggest blocks, with j being on even positions
vector<vector<ll>> dp;

vector<vector<int>> C;

void precalculate(void)
{
    C.resize(MAXV + 1, vector<int>(MAXV + 1));
    C[0][0] = 1;
    for (int i = 1; i <= MAXV; i++) {
        C[i][0] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
        C[i][i] = 1;
    }
}

ll choose(int a, int b)
{
    if (b > a || b < 0) {
        return 0;
    }

    return C[a][b];
}

void solve(void)
{
    scanf("%d", &N);


    a.resize(N);
    dp.assign(N + 1, vector<ll>(N + 1, 0));

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    reverse(a.begin(), a.end());

    dp[0][0] = 1;
    for (int i = 0; i < N; i++) {
        int cnt = 1;
        while (i != N - 1 && a[i + 1] == a[i]) {
            dp[i + 1] = dp[i];
            cnt++;
            i++;
        }
        for (int j = 0; j <= min(i, N / 2); j++) {
            
            // Calculate number of empty odd spots in which we are able to place numbers of value a[i]
            int empty = max(j - 1, 0);
            if (j == N / 2) {
                empty++;
            }
            empty -= (i - j) - (cnt - 1);
            empty = max(empty, 0);


            // Choose to place all numbers of same value on odd spots
            dp[i + 1][j] += (ll)dp[i][j] * choose(empty, cnt);

            // Place one number of this value on even spot
            dp[i + 1][j + 1] += (ll)dp[i][j] * choose(empty, cnt - 1);
            
            dp[i + 1][j] %= MOD;
            dp[i + 1][j + 1] %= MOD;
        }
    }

    printf("%lld\n", dp[N][N / 2]);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    precalculate();
    while (t--) {
        solve();
    }

    return 0;
}