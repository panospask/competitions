#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, k;
int a[MAXN + 5];

int main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int q = 0; q < k; q++) {
        int x;
        scanf("%d", &x);

        int l = -1; // a[l] <= x
        int r = n; // a[r] > x

        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (a[mid] <= x)
                l = mid;
            else 
                r = mid;
        }

        printf("%d\n", r);
    }

    return 0;
}