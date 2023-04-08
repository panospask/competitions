#include <bits/stdc++.h>
#define MAXN 1000

using namespace std;

bool hastree[MAXN + 2][MAXN + 2];

// ttl_trees[i][j]: The total number of trees from (0,0) to (i,j)
int n, q;
int ttl_trees[MAXN + 2][MAXN + 2];

int main(void)
{
    scanf("%d %d", &n, &q);

    for (int i = 1; i <= n; i++) {
        getchar();
        for (int j = 1; j <= n; j++) {
            char c = getchar();
            hastree[i][j] = c == '*';
        }
    }

    ttl_trees[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ttl_trees[i][j] = ttl_trees[i-1][j] + ttl_trees[i][j-1] - ttl_trees[i-1][j-1] + hastree[i][j];
        }
    }

    while (q--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        int ans = ttl_trees[x2][y2] - ttl_trees[x1 - 1][y2] - ttl_trees[x2][y1 - 1] + ttl_trees[x1 - 1][y1 - 1];
        printf("%d\n", ans);
    }

    return 0;
}