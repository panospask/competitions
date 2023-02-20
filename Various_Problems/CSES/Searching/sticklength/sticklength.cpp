#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int sticks[MAXN + 5];
int n;

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &sticks[i]);
    sort(sticks, sticks + n);

    int value_to_make = sticks[n/2];
    long long int total_val = 0;
    for (int i = 0; i < n; i++)
        total_val += abs(sticks[i] - value_to_make);

    printf("%lld\n", total_val);
    return 0;
}