#include <bits/stdc++.h>

using namespace std;

int x, k;

void solve(void)
{
    scanf("%d %d", &x, &k);
    if (x % k == 0)
        printf("2\n%d %d\n", x + 1, -1);
    else
        printf("1\n%d\n", x);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while(t--)
        solve();

    return 0;
}