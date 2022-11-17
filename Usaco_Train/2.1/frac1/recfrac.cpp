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

int n;

void build_rec_frac(int d1, int n1, int d2, int n2)
{
    if (n1 + n2 > n)
        return;

    build_rec_frac(d1, n1, d1 + d2, n1 + n2);
    printf("%d/%d\n", d1 + d2, n1 + n2);
    build_rec_frac(d1 + d2, n1 + n2, d2, n2);
}

int main(void)
{
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);

    scanf("%d", &n);

    printf("0/1\n");
    build_rec_frac(0, 1, 1, 1);
    printf("1/1\n");
}