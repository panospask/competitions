#include <bits/stdc++.h>
#define MAXN (int)1e5

using namespace std;

int a[MAXN + 5];
int n, k;

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

        if (l != -1 && a[l] == x)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}