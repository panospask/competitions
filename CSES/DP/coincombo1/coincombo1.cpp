#include <bits/stdc++.h>
#define MAXX 1000000
#define MAXN 100
#define MOD ((int)1e9 + 7)

using namespace std;

long long int total_combo[MAXX + 2];
int coins[MAXN + 2];
int n, x;

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);
    sort(coins, coins + n);

    total_combo[0] = 1; // Can only get there using the empty subset
    for (int s = 0; s < x; s++) {
        for (int i = 0; i < n && coins[i] + s <= x; i++) {
            total_combo[s + coins[i]] += total_combo[s];
            total_combo[s + coins[i]] %= MOD;
        }
    }

    printf("%lld\n", total_combo[x]);
    return 0;
}