#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int n, m, q;
vector<vector<ll>> d;

int main(void)
{
    scanf("%d %d %d", &n, &m, &q);

    d.assign(n, vector<ll>(n, INF));

    for (int i = 0; i < n; i++)
        d[i][i] = 0;

    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;
        d[a][b] = d[b][a] = min(d[a][b], (ll)w);
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] != INF && d[k][j] != INF && (d[i][k] + d[k][j]) < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];

    while (q--) {
        int i, j;
        scanf("%d %d", &i, &j);
        i--; j--;

        if (d[i][j] == INF)
            printf("-1\n");
        else
            printf("%lld\n", d[i][j]);
    }

    return 0;
}