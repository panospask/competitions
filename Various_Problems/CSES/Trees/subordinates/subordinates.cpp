#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

int n;
vector<int> direct_below[MAXN + 2];
int ttl_sub[MAXN + 2];

int calc_ttl_below(int i)
{
    if (ttl_sub[i] != 0)
        return ttl_sub[i];
    
    for (auto j : direct_below[i]) {
        ttl_sub[i] += calc_ttl_below(j) + 1;    
    }

    return ttl_sub[i];
}

int main(void)
{
    scanf("%d", &n);

    int boss;    
    for (int i = 1; i < n; i++) {
        scanf("%d", &boss);
        boss--;

        direct_below[boss].pb(i);
    }

    calc_ttl_below(0);

    for (int i = 0; i < n; i++)
        printf("%d ", ttl_sub[i]);
    printf("\n");
    return 0;
}