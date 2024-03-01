#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

void solve(void)
{
    scanf("%d", &N);
    a.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());

    int ans = 2 * a[N - 1] - 2 * a[0] + 2 * a[N - 2] - 2 * a[1];

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}