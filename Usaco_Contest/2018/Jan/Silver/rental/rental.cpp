#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXM 100000
#define MAXK 100000

using namespace std;

struct company {
    int ppl;
    int litters;
};
typedef struct company Company;

bool operator < (Company a, Company b)
{
    if (a.ppl == b.ppl)
        return a.litters < b.litters;

    return a.ppl > b.ppl;
}

int n, m, r;
int milkprod[MAXN + 5];
Company companies[MAXM + 5];
int farmers[MAXK + 5];
int profit_from[MAXN + 5];

int main(void)
{
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &r);
    for (int i = 0; i < n; i++)
        scanf("%d", &milkprod[i]);
    sort(milkprod, milkprod + n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &companies[i].litters, &companies[i].ppl);
    }
    sort(companies, companies + m);
    for (int i = 0; i < r; i++) {
        scanf("%d", &farmers[i]);
    }
    sort(farmers, farmers + r);
    reverse(farmers, farmers + r);

    // Start by using maximum companies and minimum farmers and work up to optimal from there
    long long int ttl_profit = 0;
    int cur_company = 0;
    int cur_remove;
    for (int cow = n - 1; cow >= 0 && cur_company < m; cow--) {
        profit_from[cow] = 0;
        while (milkprod[cow] > 0 && cur_company < m) {
            cur_remove = min(companies[cur_company].litters, milkprod[cow]);
            ttl_profit += cur_remove * companies[cur_company].ppl;
            profit_from[cow] += cur_remove * companies[cur_company].ppl;

            milkprod[cow] -= cur_remove;
            companies[cur_company].litters -= cur_remove;
            if (companies[cur_company].litters == 0)
                cur_company++;
        }
    }    

    // Work upwards from the least producing cows until it is no longer beneficial
    int cur_farmer = 0;
    for (int cow = 0; cow < n && cur_farmer < r; cow++) {
        if (farmers[cur_farmer] > profit_from[cow]) {
            ttl_profit -= profit_from[cow];
            ttl_profit += farmers[cur_farmer];
            cur_farmer++;
        }
    }

    printf("%lld\n", ttl_profit);
    return 0;
}