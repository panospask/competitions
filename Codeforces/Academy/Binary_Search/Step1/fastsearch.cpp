#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int n, k;
int a[MAXN + 5];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a, a + n);
    scanf("%d", &k);

    for (int q = 0; q < k; q++) {
        int q_l, q_r;
        scanf("%d %d", &q_l, &q_r);

        // Find pos of first value lower than q_l
        int l = -1; // a[l] < q_l
        int r = n; // a[r] >= q_l
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (a[mid] < q_l)
                l = mid;
            else 
                r = mid;
        }
        int first_lower = l;

        // Find pos of first value higher than q_r
        l = -1; // a[l] <= q_l
        r = n; // a[r] > q_r
        while (r > l + 1) {
            int mid = (l + r) / 2;
            if (a[mid] <= q_r)
                l = mid;
            else 
                r = mid;
        }
        int first_higher = r;

        int ans = first_higher - first_lower - 1;
        printf("%d\n", ans);
    }
    return 0;
}
