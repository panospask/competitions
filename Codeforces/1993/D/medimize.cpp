#include <bits/stdc++.h>

using namespace std;

const int INF = 1e6;

int N, K;
int rem;
vector<int> a;

/* dp[i]:
 * The optimal placement of the first (i % K) + 1 numbers
 * in the reduced array
 */
vector<int> dp;

bool test(int med)
{
    dp.resize(N);

    dp[0] = a[0] >= med ? 1 : -1;

    for (int i = 1; i < N; i++) {
        int v = a[i] >= med ? 1 : -1;

        if (i % K == 0) { 
            // Return to the beggining of the reduced array
            dp[i] = max(v, dp[i - K]);
        }
        else {
            // Add current number
            dp[i] = dp[i - 1] + v;
            if (i > K) {
                // Maybe adding one of the previous numbers in this position is optimal
                dp[i] = max(dp[i], dp[i - K]);
            }
        }
    }

    return dp[N - 1] > 0;
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);

    rem = N - (N / K) * K;
    if (rem == 0) {
        rem = K;
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    int l = 0;
    int r = 1e9 + 1;

    while (l + 1 < r) {
        int mid = ((long long )l + r) / 2;
        if (test(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%d\n", l);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}