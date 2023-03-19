#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

long long int pref_sum[MAXN + 2];
int a[MAXN + 2];
int n, q;

bool is_odd_mult(long long  a, long long  b)
{
    return (a % 2 && b % 2);
}

void solve(void)
{
    scanf("%d %d", &n, &q);
    
    pref_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pref_sum[i] = pref_sum[i-1] + a[i];
    }

    long long int ttl_sum = pref_sum[n];
    bool is_odd_total = ttl_sum % 2;

    for (int x = 0; x < q; x++) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);

        long long int cursum = pref_sum[r] - pref_sum[l-1];
        bool isodd = is_odd_mult(r - l + 1, k);

        bool differs = (isodd != (cursum % 2));

        if ((is_odd_total && !differs) || (!is_odd_total && differs))
            printf("YES\n");
        else 
            printf("NO\n");
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
        solve();
}