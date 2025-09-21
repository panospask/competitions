#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N;
vector<int> a, b;

// dp[i][s]: Number of good subsets up to i. s if we have swapped a[i] and b[i]
vector<vector<ll>> dp;

void solve(void) {
    scanf("%d", &N);

    a.resize(N + 1);
    b.resize(N + 1);
    dp.assign(N + 1, vector<ll>(2, 0));

    a[0] = b[0] = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &b[i]);
    }

    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int s1 = 0; s1 < 2; s1++) {
            int a1 = a[i];
            int b1 = b[i];
            if (s1) {
                swap(a1, b1);
            }

            for (int s2 = 0; s2 < 2; s2++) {
                int a2 = a[i - 1];
                int b2 = b[i - 1];
                if (s2) {
                    swap(a2, b2);
                }

                if (a1 >= a2 && b1 >= b2) {
                    dp[i][s1] = (dp[i][s1] + dp[i - 1][s2]) % MOD;
                }
            }
        }
    }

    printf("%lld\n", (dp[N][0] + dp[N][1]) % MOD);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}