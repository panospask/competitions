#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int a[MAXN + 2];
int xor_sum[MAXN + 2];
int n, q;

int main(void)
{
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    xor_sum[0] = 0;
    for (int i = 1; i <= n; i++) 
        xor_sum[i] = xor_sum[i-1] ^ a[i-1];

    for (int x = 0; x < q; x++) {
        int l, r;
        scanf("%d %d", &l, &r);

        printf("%d\n", xor_sum[r] ^ xor_sum[l-1]);
    }

    return 0;
}