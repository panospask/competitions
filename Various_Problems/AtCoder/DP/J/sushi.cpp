#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

// Expected operations if we only consider the subarray [0..i]
vector<double> dp;

int main(void)
{
    scanf("%d", &N);

    a.resize(N + 1);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);

    dp.resize(N + 1);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        double extra = dp[i - 1] / i;
        extra = extra + i * max(0.0, (double)a[i] - extra);

        dp[i] = dp[i - 1] + extra;
    }

    printf("%.10lf\n", dp[N]);
}