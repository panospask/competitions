#include <bits/stdc++.h>
#define MAXN 1000
#define MOD 1000000007

using namespace std;

bool istrap[MAXN][MAXN];
int n;
int options[MAXN][MAXN];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < n; j++) {
            char c = getchar();
            istrap[i][j] = c == '*';
        }
    }

    options[0][0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (istrap[i][j]) continue;

            if (i != n-1)
                options[i+1][j] = (options[i+1][j] + options[i][j]) % MOD;
            if (j != n-1)
                options[i][j+1] = (options[i][j+1] + options[i][j]) % MOD;
        }

    if (istrap[n-1][n-1])
        options[n-1][n-1] = 0;

    printf("%d\n", options[n-1][n-1]);
    return 0;
}