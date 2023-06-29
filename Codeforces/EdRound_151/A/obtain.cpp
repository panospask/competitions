#include <bits/stdc++.h>

using namespace std;

void solve(void)
{
    int n, k, x;

    scanf("%d %d %d", &n, &k, &x);

    vector<int> lateused;
    lateused.assign(n + 1, -1);

    for (int i = 1; i <= k; i++)
        if (i != x)
            lateused[i] = i;

    for (int i = 1; i < n; i++) {
        if (lateused[i] == -1)
            continue;
        for (int j = 1; j + i <= n && j <= k; j++) {
            if (x == j)
                continue;
            if (lateused[i + j] == -1)
                lateused[i + j] = j;
        }
    }

    if (lateused[n] == -1) {
        printf("NO\n");
        return;
    }

    vector<int> ans;
    while (n != 0) {
        ans.push_back(lateused[n]);
        n -= lateused[n];
    }

    printf("YES\n%d\n", (int)ans.size());
    for (auto e : ans)
        printf("%d ", e);
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