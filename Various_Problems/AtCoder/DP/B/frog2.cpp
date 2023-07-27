#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9;

int N, K;
vector<int> h;
vector<int> dp;

int main(void)
{
    scanf("%d %d", &N, &K);

    dp.resize(N);

    h.resize(N);
    for (int i = 0; i < N; i++)
        scanf("%d", &h[i]);

    dp.assign(N, INF);

    dp[0] = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j <= i + K && j < N; j++)
            dp[j] = min(dp[j], dp[i] + abs(h[i] - h[j]));
    }

    printf("%d\n", dp[N - 1]);

    return 0;
}