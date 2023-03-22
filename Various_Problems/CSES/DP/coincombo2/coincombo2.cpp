#include <bits/stdc++.h>
#define MAXX (int)1e6
#define MAXN (int)1e2
#define MOD ((int)1e9 + 7)

using namespace std;

// coin_combo[i][s]: Total ways to reach sum s using only the first i coins, in order
long long int coin_combo[MAXX + 2];
int coins[MAXN + 2];
int n, x;

int main(void)
{
    scanf("%d %d", &n, &x);
    for (int i = 1; i <= n; i++)
        scanf("%d", &coins[i]);
    sort(coins + 1, coins + n + 1);

    coin_combo[0] = 1;
    for (int i = 1; i <= n; i++) {
        // Calculate coin_combo using only the first i coins
        for (int s = 1; s <= x; s++) {
            if (s >= coins[i]) {
                coin_combo[s] += coin_combo[s - coins[i]];
                coin_combo[s] %= MOD;
            }
        }
    }

    printf("%lld\n", coin_combo[x]);
    return 0;
}