/*
ID: panos.p1
LANG: C++11
TASK: fact4
*/

#include <bits/stdc++.h>
#define MAXN 5000

using namespace std;
long long int dp[MAXN + 5];
int n;
int fac5 = 0, fac2 = 0;
int twof[] = {6, 2, 4, 8};

int main(void)
{
    freopen("fact4.in", "r", stdin);
    freopen("fact4.out", "w", stdout);

    scanf("%d", &n);

    if (n == 1) {
        printf("%d\n", 1);
        return 0;
    }

    int num;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        num = i;
        while (num % 2 == 0) {
            num /= 2;
            fac2++;
        }
        while (num % 5 == 0) {
            num /= 5;
            fac5++;
        }

        dp[i] = dp[i-1] * num;
        dp[i] %= 10;
    }

    int rmv = min(fac2, fac5);
    fac2 -= rmv;
    fac5 -= rmv;
    long long int ans = dp[n];
    ans *= twof[fac2 % 4];

    printf("%lld\n", ans % 10);
    return 0;
}