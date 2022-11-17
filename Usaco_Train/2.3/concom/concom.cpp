/*
ID: panos.p1
LANG: C++
TASK: concom
*/


#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
int share[102][102];
int controlled_by[102];
bool controls[102][102];
int n;

void make_controller(int i, int j)
{
    if (controls[i][j])
        return;

    if (controlled_by[j] == j)
        controlled_by[j] = i;
    controls[i][j] = true;

    for (int k = 0; k <= n; k++) {
        share[i][k] += share[j][k];
        if (share[i][k] > 50 && !controls[i][k])
            make_controller(i, k);
    }

    if (controlled_by[i] != i)
        make_controller(controlled_by[i], j);
}

int main(void)
{
    freopen("concom.in", "r", stdin);
    freopen("concom.out", "w", stdout);

    for (int i = 1; i <= 100; i++)
        controlled_by[i] = i;

    int m;
    scanf("%d", &m);

    int own;
    int con;
    int val;
    n = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &own, &con, &val);
        n = max(max(own, con), n);
        share[own][con] = val;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (share[i][j] > 50)
                make_controller(i, j);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            if (controls[i][j] && i != j)
                printf("%d %d\n", i, j);
    }

    return 0;
}