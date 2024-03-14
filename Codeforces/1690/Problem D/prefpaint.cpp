#include <bits/stdc++.h>

using namespace std;

bool arr[200005];
int one_sum[200005];
int n, k;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        scanf("%d %d", &n, &k);
        getchar();

        arr[0] = getchar() == 'W';
        one_sum[0] = arr[0];

        for (int i = 1; i < n; i++) {
            arr[i] = getchar() == 'W';
            one_sum[i] = arr[i] + one_sum[i - 1];
        }

        int minval = INT_MAX;
        for (int i = k - 1; i < n; i++) {
            minval = min(one_sum[i] - one_sum[i - k], minval);
        } 

        printf("%d\n", minval);
    }
}