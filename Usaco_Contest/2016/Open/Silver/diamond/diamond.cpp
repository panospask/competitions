#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

int n, k;
int a[MAXN];
int max_low_sub[MAXN];
int max_high_sub[MAXN];

int main(void)
{
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    sort(a, a + n);

    // Calculate tha max subarray that has only numbers lower than a[i]
    int cur_sub_start = 0;
    int max_sub_num = 0;
    max_low_sub[0] = 0;
    for (int i = 1; i < n; i++) {
        while (a[i-1] - a[cur_sub_start] > k)
            cur_sub_start++;

        max_low_sub[i] = max(max_low_sub[i - 1], i - cur_sub_start);
    }

    // Calculate the max subarray that has only numbers higher than or equal to a[i]
    max_high_sub[n - 1] = 1;
    cur_sub_start = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        while (a[cur_sub_start] - a[i] > k)
            cur_sub_start--;

        max_high_sub[i] = max(max_high_sub[i - 1], cur_sub_start - i + 1);
    }

    int maxans = 0;
    for (int i = 0; i < n; i++) {
        maxans = max(maxans, max_low_sub[i] + max_high_sub[i]);
    }

    printf("%d\n", maxans);
}