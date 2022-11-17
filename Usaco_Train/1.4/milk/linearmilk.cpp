/*
ID: panos.p1
LANG: C++
TASK: milk
*/

#include <bits/stdc++.h>

using namespace std;

//Prices have low upper bound --> counting sort
long long int milk_per_price[1001];
long long int n, m;

int main(void)
{
    freopen("milk.in", "r", stdin);
    freopen("milk.out", "w", stdout);

    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < m; i++) {
        int price, amount;
        scanf("%d %d", &price, &amount);

        milk_per_price[price] += amount;
    }

    long long int total_cost = 0;
    for (int i = 0; i <= 1000 && n > 0; i++) {
        long long int buy = min(milk_per_price[i], n);

        n -= buy;
        total_cost += buy * i;
    }

    printf("%lld\n", total_cost);
    return 0;
}