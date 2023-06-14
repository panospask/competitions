#include <bits/stdc++.h>

using namespace std;

const int K = 25;

int n, q;
vector<vector<int>> sparse;
vector<int> a;
vector<int> lg;

int main(void)
{
    scanf("%d %d", &n, &q);

    a.resize(n);
    lg.resize(n + 2);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    lg[1] = 0;
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    sparse.assign(25, vector<int>(n, INT_MAX));

    for (int i = 0; i < n; i++)
        sparse[0][i] = a[i];

    for (int up = 1; up <= lg[n]; up++)
        for (int i = 0; i + (1 << up) - 1 < n; i++) {
            sparse[up][i] = min(sparse[up - 1][i], sparse[up - 1][i + (1 << (up-1))]);
        }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int len = r - l;

        int up = lg[len];

        int ans = min(sparse[up][l], sparse[up][r - (1<<up)]);
        printf("%d\n", ans);
    }

    return 0;
}