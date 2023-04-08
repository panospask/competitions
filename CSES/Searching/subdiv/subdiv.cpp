#include <bits/stdc++.h>
#define MAXN 200000
#define MOD(a, m) (((a%m)+m)%m)

using namespace std;

int n;
int a[MAXN + 2];
long long int pref_sum[MAXN + 2];
long long int leave_rem[MAXN + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    pref_sum[0] = 0;
    leave_rem[0] = 1;
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i-1] + a[i];
        pref_sum[i] = MOD(pref_sum[i], n);

        ans += leave_rem[pref_sum[i]];

        leave_rem[pref_sum[i]]++;
    }

    printf("%lld\n", ans);
    return 0;
}