/*
ID: panos.p1
LANG: C++
TASK: milk
*/

#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
typedef pair<int, int> ii;

ii farmers[5005];
int n, m;

int main(void)
{
    freopen("milk.in", "r", stdin);
    freopen("milk.out", "w", stdout);

    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &farmers[i].first, &farmers[i].second);
    }
    sort(farmers, farmers + m);

    long long int total_cost = 0;
    int cur_farm = 0;
    while (n > 0) {
        int buy = min(farmers[cur_farm].second, n);

        n -= buy;
        total_cost += (long long int) buy * farmers[cur_farm].first;

        cur_farm++;
    }

    printf("%lld\n", total_cost);
}