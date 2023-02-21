#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n, x;
int stick_sizes[MAXN + 5];

bool greatercomp(int a, int b)
{
    return a > b;
}

long long int cost_of(int sticksize, int earliest_accept, int earliest_reject)
{
    if (earliest_accept + 1 >= earliest_reject)
        return 0;

    int cursum = 0;
    int i;
    for (i = earliest_accept; i < earliest_reject; i++) {
        if (cursum >= sticksize / 2)
            break;
        cursum += stick_sizes[i];
    }

    return sticksize + cost_of(cursum, earliest_accept, i) + cost_of(sticksize - cursum, i, earliest_reject);
}

int main(void)
{
    scanf("%d %d", &x, &n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &stick_sizes[i]);
    sort(stick_sizes, stick_sizes + n);

    long long int ttl_cost = cost_of(x, 0, n);
    printf("%lld\n", ttl_cost);
    return 0;
}