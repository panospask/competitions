/*
ID: panos.p1
LANG: C++11
TASK: fact4
*/

#include <bits/stdc++.h>
#define MAXN 5000

using namespace std;

int fact[MAXN + 5];
int n;

int main(void)
{
    freopen("fact4.in", "r", stdin);
    freopen("fact4.out", "w", stdout);

    scanf("%d", &n);

    fact[0] = 1;
    // for (int i = 1; i <= n; i++) {
    //     fact[i] = fact[i-1] * i;
    //     while (fact[i] % 10 == 0)
    //         fact[i] /= 10;
    //     int mod_by = pow(10, (int)log10(i) + 1);
    //     fact[i] %= mod_by;
    // }
    fact[0] = 1;
    for (int i = 1; i < n; i++) {
        fact[i] = fact[i-1] * i;
        while (fact[i] % 10 == 0)
            fact[i] /= 10;
    }

    printf("%d\n", fact[n] % 10);
    return 0;
}