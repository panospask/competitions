/*
ID: panos.p1
LANG: C++11
TASK: kimbits
*/

#include <bits/stdc++.h>
#define MAXN 32

using namespace std;

unsigned long long int dp[MAXN][MAXN];
long long int n, k, l;
unsigned long long int num[MAXN][MAXN];
string ans;

int main(void)
{
    freopen("kimbits.in", "r", stdin);
    freopen("kimbits.out", "w", stdout);

    scanf("%lld %lld %lld", &n, &l, &k);

    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            if (j == 0)
                dp[i][j] = 1;
            else {
                dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
            }
        }

    for (int i = 0; i <= 31; i++) {
        num[i][0] = 1;
        num[0][i] = 1;
    }

    for (int i = 1; i <= 31; i++)
        for (int j = 1; j <= 31; j++)
            num[i][j] = num[i][j-1] + dp[i][j];

    for (int i = n; i > 0; i--) {
        long long x = num[i-1][l];
        if (k > x) {
            ans.push_back('1');
            k -= x;
            l--;
        }
        else 
            ans.push_back('0');
    }

    cout << ans << '\n';
    return 0;
}