#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e14;

int n, q;
vector<int> p;
vector<ll> dp;

int main(void)
{
    scanf("%d %d", &n, &q);

    p.resize(n + 1);
    dp.assign(n + 1, INF);
    p[0] = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    sort(p.begin(), p.end());

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        // Add i as a lone purchase
        dp[i] = dp[i - 1] + (p[i] / 100) * (100 - q);

        // Add i as the priciest item of an offer
        // The only offer that makes sense is i, i - 1, i - 2
        // All other offers are suboptimal

        if (i >= 3) {
            // i - 2 will be given to us for free
            dp[i] = min(dp[i], dp[i - 3] + p[i] + p[i - 1]);
        }
    }

    printf("%lld\n", dp[n]);

    return 0;
}