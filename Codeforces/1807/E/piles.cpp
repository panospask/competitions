#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int a[MAXN + 2];
long long int pref_sum[MAXN + 2];
int n;

bool check_if_bad_stone_contained(int l, int r)
{
    printf("? %d", r - l + 1);

    for (int i = l; i <= r; i++)
        printf(" %d", i);
    printf("\n");
    fflush(stdout);


    long long int x;
    scanf("%lld", &x);

    if (x != pref_sum[r] - pref_sum[l-1])
        return true;
    else 
        return false;
}

void solve(void)
{
    scanf("%d", &n);
    pref_sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pref_sum[i] = a[i] + pref_sum[i - 1];
    }

    int l = 1;
    int r = n;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (check_if_bad_stone_contained(l, mid))
            r = mid;
        else 
            l = mid;
    }
    // Between l and r
    if (check_if_bad_stone_contained(r, r))
        l = r;

    printf("! %d\n", l);
    fflush(stdout);
}

int main(void)
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++)
        solve();
}