/*
ID: panos.p1
LANG: C++
TASK: money
*/


#include <bits/stdc++.h>

using namespace std;

int coins[27];
int n, v;

long long int ans;

void dfs(int sum, int latest_i)
{
    if (sum >= n) {
        if (sum == n)
            ans++;
        return;
    }

    int next_coin;
    for (int i = latest_i + 1; i < v; i++) {
        next_coin = coins[i];
        for (int j = 1; j * next_coin <= n - sum; j++)
            dfs(sum + j * next_coin, i);
    }

    return;
}

int main(void)
{
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);

    scanf("%d %d", &v, &n);

    for (int i = 0; i < v; i++)
        scanf("%d", &coins[i]);
    dfs(0, -1);

    printf("%lld\n", ans);
}
