/*
ID: panos.p1
LANG: C++11
TASK: vans
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define BASE ((int)10e6)
#define MAXN 1000

using namespace std;

struct bignum {
    int base = BASE;
    int l;
    int num[100];

    bignum(int a){this->l = 1; this->num[0] = a;}
    bignum(void){this->l = 0;}
};
typedef struct bignum Bignum;

Bignum operator + (Bignum a, Bignum b) 
{
    int maxl, rem = 0;
    maxl = max(a.l, b.l);
    int i = 0;

    Bignum c(0);
    int to_add;

    while (i < maxl || rem != 0) {
        to_add = rem;

        if (i < a.l)
            to_add += a.num[i];
        if (i < b.l)
            to_add += b.num[i];

        c.num[i] = to_add % BASE;
        rem = to_add / BASE;

        i++;
    }

    c.l = i;
    return c;
}

Bignum operator * (int a, Bignum b)
{
    int to_add, rem = 0;
    int i = 0;
    Bignum c(0);

    while (i < b.l || rem != 0) {
        to_add = rem;
        
        if (i < b.l)
            to_add += b.num[i] * a;

        c.num[i] = to_add % BASE;
        rem = to_add / BASE;

        i++;
    }

    c.l = i;
    return c;
}

void prnt_bignum(Bignum a)
{
    printf("%d", a.num[a.l-1]);
    for (int i = a.l - 2; i >= 0; i--)
        printf("%.7d", a.num[i]);
    printf("\n");
}

Bignum a[MAXN], b[MAXN], c(0);
int n;

int main(void)
{
    freopen("vans.in", "r", stdin);
    freopen("vans.out", "w", stdout);

    scanf("%d", &n);

    a[0] = Bignum(0); b[0] = Bignum(2);
    a[1] = Bignum(2); b[1] = Bignum(2);
    c = Bignum(2);

    for (int i = 2; i < n; i++) {
        a[i] = a[i-1] + b[i-1];
        c = c + 2 * a[i-2];
        b[i] = 2 * a[i-1] + b[i-2] + c;
    }

    prnt_bignum(a[n-1]);
    return 0;
}