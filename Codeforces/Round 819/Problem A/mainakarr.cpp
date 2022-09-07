#include <bits/stdc++.h>
#define MAXN 2000

using namespace std;

int n;
int arr[MAXN];
int t;
int main(void)
{
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        int ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans = max(ans, arr[i] - arr[i+1]);
            ans = max(ans, arr[i+1] - arr[0]);
            ans = max(ans, arr[n-1] - arr[i]);
        }

        printf("%d\n", ans);
    }

    return 0;
}