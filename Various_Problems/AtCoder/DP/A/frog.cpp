#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int min_cost[MAXN + 2];
int n;
int h[MAXN + 2];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &h[i]);

    // Frog is at stone 0, the cost is 0
    min_cost[0] = 0;
    // Only one way to go to stone one
    min_cost[1] = min_cost[0] + abs(h[0] - h[1]);
    
    for (int i = 2; i < n; i++) 
        min_cost[i] = min(min_cost[i-1] + abs(h[i] - h[i-1]), min_cost[i-2] + abs(h[i] - h[i-2]));

    printf("%d\n", min_cost[n-1]);
    return 0;
}