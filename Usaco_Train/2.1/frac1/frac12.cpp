/*
ID: panos.p1
LANG: C++
TASK: frac1
*/

#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;
typedef pair<long double, ii> lii;

int gcd(int a,int b){
    if(b==0)return a;
    else return gcd(b,a%b);
}

int lcm(int a,int b){
    return a*b/gcd(a,b);
}

int main(void)
{
    freopen("frac1.in", "r", stdin);
    freopen("frac1.out", "w", stdout);

    int n;
    scanf("%d", &n);

    long long int mult_by = 1;
    for (int i = n; i > 1; i--)
        mult_by = lcm(mult_by, i);

    set<lii> order;

    for (int i = n; i >= 1; i--)
        for (int j = i - 1; j >= 1; j--)
            if (gcd(i, j) == 1)
                order.insert(mp((long double)(j * 1) / i, mp(j, i)));

    for (int j = n; j > 1; j--)
        order.insert(mp((long double)1 / j, mp(1, j)));

    // Remember 0 and 1
    printf("0/1\n");
    for (auto& val : order)
        printf("%d/%d\n", val.second.first, val.second.second);
    printf("1/1\n");
}