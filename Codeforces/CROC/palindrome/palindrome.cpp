#include <bits/stdc++.h>
#define MAXN 5000

using namespace std;

int n, q;
// pal[l][r] determines if the string [l..r] is palindrome
bool pal[MAXN + 2][MAXN + 2];
long long int dp[MAXN + 2][MAXN + 2];
char s[MAXN + 2];

int main(void)
{

    char c = getchar();
    int i = 0;
    while (c != '\n') {
        s[i++] = c;
        c = getchar();
    }

    n = i;

    for (int len = 1; len <= n; len++) 
        for (int l = 0; l <= n - len; l++) {
            int r = len + l - 1;

            if (l == r) {
                pal[l][r] = true;
                dp[l][r] = 1;
            }
            else if (l == r - 1) {
                pal[l][r] = s[l] == s[r];

                dp[l][r] = dp[l][l] + dp[r][r] + pal[l][r];
            }
            else {
                pal[l][r] = pal[l+1][r-1] && (s[l] == s[r]);

                dp[l][r] = dp[l+1][r] + dp[l][r-1] - dp[l+1][r-1] + pal[l][r];
            }
        }

    // Now proccess the queries
    scanf("%d", &q);
    int a, b;
    while (q--) {
        scanf("%d %d", &a, &b);
        a--; b--;

        printf("%lld\n", dp[a][b]);
    }

    return 0;
}