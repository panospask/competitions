#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 9;

int N, D;
vector<int> a;

// avail[i]: Number of blocks with side length smaller than a[i] and bigger than a[i] + D
vector<int> avail;

// dp[i]: Number of ways to arrange the first i blocks
vector<ll> dp;

int main(void)
{
    scanf("%d %d", &N, &D);

    a.resize(N);
    avail.resize(N);
    dp.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());
    int j = 0;
    for (int i = 0; i < N; i++) {
        while (a[j] + D < a[i]) {
            j++;
        }

        avail[i] = i - j + 1;
    }

    dp[0] = 1;
    for (int i = 0; i < N; i++) {
        dp[i + 1] = dp[i] * avail[i] % MOD;
    }

    printf("%lld\n", dp[N]);

    return 0;
}