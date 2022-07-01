/*
ID: panos.p1
LANG: C++
TASK: skidesign
*/

#include <bits/stdc++.h>
#define MAX_DIFF 17
#define MAXN 1000
#define MAX_HEIGHT 100

using namespace std;

int hill_level[MAXN];
int n;

long long int find_cost(int low, int high)
{
    long long int ttl_cost = 0;

    int level;
    for (int i = 0; i < n; i++) {
        level = hill_level[i];
        if (level < low) {
            ttl_cost += pow(low - level, 2);
        }
        else if (level > high) {
            ttl_cost += pow(level - high, 2);
        }
    }

    return ttl_cost;
}

int main(void)
{
    freopen("skidesign.in", "r", stdin);
    freopen("skidesign.out", "w", stdout);

    scanf("%d", &n);

    int max_hill = -1;

    for (int i = 0; i < n; i++) {
        scanf("%d", &hill_level[i]);
        max_hill = max(max_hill, hill_level[i]);
    }

    long long int solution = LONG_LONG_MAX;
    for (int i = 0; i <= max_hill - MAX_DIFF; i++) {
        solution = min(solution, find_cost(i, i + MAX_DIFF));
    }

    printf("%lld\n", solution);
    return 0;
}