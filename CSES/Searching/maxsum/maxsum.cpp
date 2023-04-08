#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int a[MAXN + 2];
long long pref_sum[MAXN + 2];
int n;

int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    pref_sum[0] = 0;
    long long min_psum = 0;
    long long ans = INT_MIN;
    for (int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i-1] + a[i];

        ans = max(ans, pref_sum[i] - min_psum);

        min_psum = min(min_psum, pref_sum[i]);
    }

    printf("%lld\n", ans);
    return 0;
}