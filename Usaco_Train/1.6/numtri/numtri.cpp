/*
ID: panos.p1
LANG: C++
TASK: numtri
*/

#include <bits/stdc++.h>

using namespace std;

int tree[600000];
long long int dp[600000];
int n;

long long int best_path(int row, int ind)
{

    if (row == n) {
        return tree[ind];
    }

    if (dp[ind] != -1)
        return dp[ind];

    long long int best = max(best_path(row + 1, ind + row), best_path(row + 1, ind + row + 1));

    dp[ind] = best + tree[ind];

    return best + tree[ind];
}

int main(void)
{
    freopen("numtri.in", "r", stdin);
    freopen("numtri.out", "w", stdout);

    scanf("%d", &n);
    int cnt = (n * (n + 1)) / 2;

    for (int i = 1; i <= cnt; i++) {
        scanf("%d", &tree[i]);
        dp[i] = -1;
    }


    long long int best = best_path(1, 1);

    printf("%lld\n", best);
    return 0;    
}