/*
ID: panos.p1
LANG: C++11
TASK: cowxor
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXPATHS (int)(10e7)
#define DIGBIT(i, dig) ((i >> (dig-1)) & 1)
using namespace std;

int n;
int xr[MAXN + 5];
int tree[MAXN * 7 + 5][2];
int pos[MAXN * 7 + 5];

pair<int, int> anspos;
int ans = -2;
int tot_pos = 2;
int cv;

int main(void)
{
    freopen("cowxor.in", "r", stdin);
    freopen("cowxor.out", "w", stdout);

    scanf("%d", &n);
    xr[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &xr[i]);
        xr[i] ^= xr[i-1];
        int curv = xr[i-1];

        // Place the previous value in the trie
        int k = 1;
        for (int j = 21; j >= 1; j--) {
            if (tree[k][DIGBIT(curv, j)] == 0)
                tree[k][DIGBIT(curv, j)] = tot_pos++;
            k = tree[k][DIGBIT(curv, j)];
        }

        pos[k] = i - 1;

        // Search for the best match with the current value
        curv = xr[i];
        k = 1;
        for (int j = 21; j > 0; j--) {
            if (tree[k][!DIGBIT(curv, j)])
                k = tree[k][!DIGBIT(curv, j)];
            else 
                k = tree[k][DIGBIT(curv, j)];
        }

        if ((curv ^ xr[pos[k]]) > ans) {
            ans = curv ^ xr[pos[k]];
            anspos.first = pos[k] + 1;
            anspos.second = i;
        }
    }

    printf("%d %d %d\n", ans, anspos.first, anspos.second);
    return 0;
}