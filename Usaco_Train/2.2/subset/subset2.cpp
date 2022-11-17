/*
ID: panos.p1
LANG: C++
TASK: subset
*/

#include <bits/stdc++.h>
#define MAXS ((40 * 41) / 2)

using namespace std;

int maxsum;
long long int ways[MAXS];
int n;
int cur_max = 0;

void calc_sum_with(int num)
{
    int i;
    for (i = min(maxsum, cur_max + num); i >= num; i--) 
        ways[i] = ways[i - num] + ways[i];

    cur_max = cur_max + num;
}

int main(void)
{
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);

    scanf("%d", &n);

    maxsum = (n * (n + 1)) / 2;

    if (maxsum % 2 == 1) {
        printf("0\n");
        return 0;
    }

    maxsum /= 2;
    ways[0] = 1;

    for (int i = 1; i <= maxsum; i++)
        ways[i] = 0;
    
    for (int i = 1; i <= n; i++)
        calc_sum_with(i);

    printf("%lld\n", ways[maxsum] / 2);
    return 0;
}