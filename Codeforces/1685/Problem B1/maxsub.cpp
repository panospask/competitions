#include <bits/stdc++.h>

using namespace std;

int a[100005];
int dp[100005];
int start;
int total_subs = 0;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);
        start = 0;
        total_subs = 0;

        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            dp[i] = 0;
        }

        for (int i = 2; i <= n; i++) {
            if (a[i-1] > a[i]) {
                total_subs++;
                i++;
            }
        }
        printf("%d\n", total_subs);
    }
}