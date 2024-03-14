#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;

void solve(void)
{
    scanf("%d", &n);
    a.resize(n);

    scanf("%d", &a[0]);
    int mdiff = INT_MAX;
    for (int i = 1; i < n; i++) {
        scanf("%d", &a[i]);

        mdiff = min(mdiff, a[i] - a[i - 1] + 1);
    }

    if (mdiff <= 0)
        printf("0\n");
    else
        printf("%d\n", mdiff / 2 + mdiff % 2);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}