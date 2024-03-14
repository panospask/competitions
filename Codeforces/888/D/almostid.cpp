#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, k;

ll ans = 0;

int main(void)
{
    scanf("%d %d", &n, &k);

    // Number of ways to shuffle a permutation of length i with no position having p[j] = j
    ll shuffle_ways = 0;

    // Number of ways to choose i numbers from a set of n
    ll choose_ways = 1;
    ll f_i = 1;
    for (int i = 0; i <= k; i++) {
        shuffle_ways = i * shuffle_ways + (i % 2 ? -1 : 1);

        if (i != 0)
            choose_ways = choose_ways * (n - i + 1) / i;
        else
            choose_ways = 1;

        ans += shuffle_ways * choose_ways;

    }

    printf("%lld\n", ans);
    return 0;
}