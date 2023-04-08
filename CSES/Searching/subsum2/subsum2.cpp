#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

unordered_map<long long, long long> have_found;
long long pref_sum[MAXN + 2];
long long a[MAXN + 2];
int n, x;

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);

    pref_sum[0] = 0;
    have_found[0] = 1;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i-1] + a[i];

        ans += have_found[pref_sum[i] - x];
        have_found[pref_sum[i]]++;
    }

    printf("%lld\n", ans);
    return 0;
}