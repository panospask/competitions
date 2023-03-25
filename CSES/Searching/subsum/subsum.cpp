#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, x;
int a[MAXN];

int main(void)
{
    scanf("%d %d", &n, &x);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int l = 0, r = 0, cursum = 0;
    int ans = 0;
    while (l != n) {
        while (r != n && cursum < x) {
            cursum += a[r];
            r++;
        }

        if (cursum == x)
            ans++;

        cursum -= a[l];
        l++;
    }

    printf("%d\n", ans);
    return 0;
}