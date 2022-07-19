/*
ID: panos.p1
LANG: C++11
TASK: humble
*/

#include <bits/stdc++.h>
#define MAXK 100
#define MAXN 100000

using namespace std;

long long int h[MAXN + 5];
int last[MAXN + 5];
int k, n;
int factors[MAXK];

int main(void)
{
    freopen("humble.in", "r", stdin);
    freopen("humble.out", "w", stdout);

    scanf("%d %d", &k, &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &factors[i]);

    h[0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = LONG_MAX;
        for (int j = 0; j < k; j++) {
            while(factors[j] * h[last[j]] <= h[i - 1])
                last[j]++;

            h[i] = min(h[i], factors[j] * h[last[j]]);
        }
    }

    printf("%lld\n", h[n]);
    return 0;
}