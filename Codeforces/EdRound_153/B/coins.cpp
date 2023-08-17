#include <bits/stdc++.h>

using namespace std;

int M, K, a1, ak;

void solve(void)
{
    scanf("%d %d %d %d", &M, &K, &a1, &ak);

    // Greedy use as many k coins as possible
    int need = M / K;
    int use = min(need, ak);

    M -= use * K;

    // Use as many 1 coins as possible AND make M a multiple of K
    int cur = M % K;
    M -= min(cur, a1);
    a1 -= min(cur, a1);

    int div = a1 / K;
    M -= K * div;
    M = max(M, 0);

    int ans = 0;
    ans += M % K;
    M -= ans;

    ans += M / K;

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}