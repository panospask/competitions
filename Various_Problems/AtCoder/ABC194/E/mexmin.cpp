#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> a;
vector<vector<int>> pos;

int main(void)
{
    scanf("%d %d", &n, &m);

    a.resize(n);
    pos.resize(n);

    for (int i = 0; i < n; i++)
        pos[i].push_back(-1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        pos[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++)
        pos[i].push_back(n);

    int ans = n;

    for (int i = 0; i < n; i++) {
        for (int p = 1; p < pos[i].size(); p++) {
            if (pos[i][p] - pos[i][p - 1] - 1 >= m)
                ans = min(ans, i);
        }
    }

    printf("%d\n", ans);

    return 0;
}