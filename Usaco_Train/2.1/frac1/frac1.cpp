/*
ID: panos.p1
LANG: C++
TASK: frac1
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int,int> ii;

int comp_fracs(const void* a, const void* b)
{
    const ii* f1 = (ii*)a;
    const ii* f2 = (ii*)b;

    return f1->first * f2->second - f1->second * f2->first;
}

int n;

int rprimes(int a, int b)
{
    int r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }

    return b == 1;
}

int main(void)
{
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);

    scanf("%d", &n);
  
    ii pairs[n * n];
    int k = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            if (rprimes(i, j))
                pairs[k++] = mp(i, j);
        }

    qsort(pairs, k, sizeof(ii), comp_fracs);

    printf("0/1\n");
    for (int i = 0; i < k; i++)
        printf("%d/%d\n", pairs[i].first, pairs[i].second);

    return 0;
}