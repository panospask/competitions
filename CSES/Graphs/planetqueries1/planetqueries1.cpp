#include <bits/stdc++.h>
#define MAXD 30

using namespace std;

int n, q;
vector<vector<int>> teleport;

int teleport_to(int x, int num)
{
    for (int i = 0; i < MAXD; i++)
        if (num & (1<<i))
            x = teleport[i][x];

    return x;
}

int main(void)
{
    scanf("%d %d", &n, &q);
    teleport.resize(MAXD, vector<int>(n));
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        a--;
        teleport[0][i] = a;
    }

    for (int up = 1; up < MAXD; up++)
        for (int i = 0; i < n; i++)
            teleport[up][i] = teleport[up-1][teleport[up-1][i]];

    while (q--) {
        int x, k;
        scanf("%d %d", &x, &k);
        x--;
        printf("%d\n", teleport_to(x, k) + 1);
    }

    return 0;
}