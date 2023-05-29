#include <bits/stdc++.h>

using namespace std;

void solve(void)
{
    int n;
    vector<int> a;

    scanf("%d", &n);
    a.resize(n + 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i <= n; i++) {
        printf("%d ", n + 1 - a[i]);
    }
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}