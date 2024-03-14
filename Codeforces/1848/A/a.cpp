#include <bits/stdc++.h>

using namespace std;

int t, n, m, k;

int getcol(int x, int y)
{
    return ((x % 2) + (y  % 2)) % 2;
}

void solve(void)
{
    scanf("%d %d %d", &n,  &m, &k);

    int x, y;
    scanf("%d %d", &x, &y);

    int col = getcol(x, y);

    bool found = false;
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &x, &y);

        int curcol = getcol(x, y);

        if (col == curcol)
            found = true;
    }

    if (found)
        printf("NO\n");
    else
        printf("YES\n");
}

int main(void)
{
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}