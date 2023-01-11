#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXQ 100000

using namespace std;

int zerosum[MAXN + 10];
int onesum[MAXN + 10];
int twosum[MAXN + 10];
int cows[MAXN + 10];
int n, q;

int main(void)
{
    freopen("bcount.in", "r", stdin);
    freopen("bcount.out", "w", stdout);

    scanf("%d %d", &n, &q);
    zerosum[0] = 0;
    onesum[0] = 0;
    twosum[0] = 0;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &cows[i]);
        cows[i]--;
        zerosum[i] = zerosum[i-1];
        onesum[i] = onesum[i-1];
        twosum[i] = twosum[i-1];

        if (cows[i] == 0)
            zerosum[i]++;
        else if (cows[i] == 1)
            onesum[i]++;
        else
            twosum[i]++;
    }

    int a, b;
    for (int j = 0; j < q; j++) {
        scanf("%d %d", &a, &b);
        printf("%d %d %d\n", zerosum[b] - zerosum[a-1], onesum[b] - onesum[a - 1], twosum[b] - twosum[a - 1]);
    }

    return 0;
}

