#include <bits/stdc++.h>

using namespace std;

struct query {
    int d;
    int rem;
};
typedef struct query Query;

int n, k;
vector<int> container;
vector<vector<int>> dp;
int approp;

int main(void)
{
    scanf("%d %d", &n, &k);
    approp = sqrt(n);
    container.assign(n, 0);
    dp.resize(approp, vector<int>(n));
    for (int i = 0; i < k; i++) {
        int a, l, d;
        scanf("%d %d %d", &a, &l, &d);
        a--;
        if (d < approp) {
            dp[d][a]++;
            if (a + d * l < n)
                dp[d][a + d * l]--;
        }
        else {
            for (int m = 0; m < l; m++)
                container[a + m * d]++;
        }
    }

    for (int d = 0; d < approp; d++) {
        for (int i = 0; i < n; i++) {
            if (i - d >= 0)
                dp[d][i] += dp[d][i - d];
            container[i] += dp[d][i];
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d", container[i]);
        if (i != n-1)
            printf(" ");
        else
            printf("\n");
    }

    return 0;
}