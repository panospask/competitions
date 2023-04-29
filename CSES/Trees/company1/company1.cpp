#include <bits/stdc++.h>

using namespace std;

int n, q;
vector<vector<int>> ancestors;
vector<int> p;

int move_up(int x, int l)
{
    while (x != -2 && l != 0) {
        int firstace = __builtin_ctz(l);
        x = ancestors[firstace][x];
        l -= (1<<firstace);
    }

    return x;
}

int main(void)
{
    scanf("%d %d", &n, &q);
    p.resize(n);
    ancestors.resize(ceil(log2(n) + 1), vector<int>(n));
    for (int i = 1; i < n; i++) {
        int e;
        scanf("%d", &e);
        e--;
        p[i] = e;
    }
    p[0] = -2;

    for (int i = 0; i < n; i++)
        ancestors[0][i] = p[i];
    for (int up = 1; up <= ceil(log2(n)); up++) {
        for (int i = 0; i < n; i++)
            if (ancestors[up - 1][i] != -2) {
                ancestors[up][i] = ancestors[up-1][ancestors[up-1][i]];
            }
            else {
                ancestors[up][i] = -2;
            }
    }

    for (int i = 0; i < q; i++) {
        int a, levels;
        scanf("%d %d", &a, &levels);
        a--;
        printf("%d\n", move_up(a, levels) + 1);
    }
}