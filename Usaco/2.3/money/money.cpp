/*
ID: panos.p1
LANG: C++
TASK: money
*/

#include <bits/stdc++.h>

using namespace std;

long long int diff_ways[10005];
int coins[25];
int n, v;
bool cur_used[10005];


void add_coin(int i)
{
    int coinval = coins[i];

    for (int i = coinval; i <= n; i++)
        diff_ways[i] += diff_ways[i - coinval];
}

void make_num(int i)
{
    if (i == 0) {
        diff_ways[i] = 1;
        return;
    }

    int curcoin = 0;
    while (coins[curcoin] <= i && curcoin < v) {
        diff_ways[i] += diff_ways[i - coins[curcoin]];
        curcoin++;
    }
}

int main(void)
{
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);

    scanf("%d %d", &v, &n);
    for (int i = 0; i < v; i++)
        scanf("%d", &coins[i]);

    sort(coins, coins + v);

    for (int i = 0; i <= n; i++)
        diff_ways[i] = 0;

    diff_ways[0] = 1;


    for (int i = 0; i <= n; i++)
        make_num(i);
    
    printf("%lld\n", diff_ways[n]);
    return 0;
}