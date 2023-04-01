#include <bits/stdc++.h>
#define MAXN 100000
#define MAXA 512

using namespace std;

int n;
int a[MAXN + 2];
int dp[MAXN + 2][MAXA + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);


    dp[0][0] = 0;
    for (int i = 0; i <= n; i++)
        for (int v = 0; v <= MAXA; v++)
            dp[i][v] = INT_MAX;

    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int val = 0; val <= MAXA; val++) {
            if (dp[i-1][val] != INT_MAX) {
                dp[i][val] = min(dp[i][val], dp[i-1][val]);

                if (a[i] > dp[i-1][val])  
                    dp[i][val ^ a[i]] = min(dp[i][val ^ a[i]], a[i]);
            }
        }

    vector<int> ans;
    for (int v = 0; v <= MAXA; v++)
        if (dp[n][v] != INT_MAX)
            ans.push_back(v);

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}