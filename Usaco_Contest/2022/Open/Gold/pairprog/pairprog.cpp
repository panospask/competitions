#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 2000
#define MOD ((int)1e9 + 7)

using namespace std;

long long int dp[MAXN + 2][MAXN + 2];
int n, m;
char a[MAXN + 2];
char b[MAXN + 2];

bool isplus(char a)
{
    return a == '+';
}

int solve(void)
{
    scanf("%d", &n);
    m = n;

    scanf(" %s", a + 1);
    scanf(" %s", b + 1);

    dp[0][0] = 1;
    for (int i = 0; i <= n; i++)
        dp[i][0] = 1;
    for (int j = 0; j <= m; j++)
        dp[0][j] = 1;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (isplus(a[i]) && isplus(b[j])) {
                dp[i][j] = (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
            }
            else if (!isplus(a[i]) && !isplus(b[j])) {
                if (a[i] == '0' && b[j] == '0')
                    dp[i][j] = 1;
                else if (a[i] == '0')
                    dp[i][j] = dp[i][j-1];
                else if (b[j] == '0')
                    dp[i][j] = dp[i-1][j];
                else 
                    dp[i][j] = (dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1]);
            }
            else {
                if (isplus(a[i]) && b[j] == '0') 
                    dp[i][j] = dp[i-1][j] + 1;
                else if (isplus(b[j]) && a[i] == '0')
                    dp[i][j] = dp[i][j-1] + 1;
                else if (isplus(a[i]) && b[j] == '1')  
                    dp[i][j] = (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
                else if (isplus(b[j]) && a[i] == '1')
                    dp[i][j] = (dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]);
                else    
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }

            dp[i][j] = (dp[i][j] + MOD) % MOD;
            if (dp[i][j] <= 0) {
                cerr << i << ' ' << j << endl;
                printf("%lld %lld %lld", dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);
                exit(EXIT_FAILURE);
            }
        }

    printf("%lld\n", dp[n][m]);
    return 0;
}

int main(void)
{
    // freopen("pairprog.in", "r", stdin);
    // freopen("pairprog.out", "w", stdout);

    int t;
    scanf("%d", &t);
    while (t--) 
        solve();
    
    return 0;
}