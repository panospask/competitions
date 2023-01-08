/* USER: paskalis35pdp
LANG: C++
TASK: coupon */

#include <bits/stdc++.h>
#define MAXN 1000
#define MAXM 10e9
#define MOD_BY 1000

using namespace std;

long int n, m;
int famnum[MAXN];
int A;
double a;

bool check_in_budget(int firstcat)
{
    int curval = firstcat;
    long int total_spent = 0;
    int i = 0;

    while (total_spent <= m && !(curval < 10) && i < n) {
        total_spent += curval * famnum[i];
        curval = (curval * A) / MOD_BY;
        i++;
    }

    if (total_spent > m)
        return false;
    else
        return true;
}

void print_ans(int value)
{
    int curval = value;
    long int total_spent = 0;
    
    for (int i = 0; i < n; i++) {
        total_spent += curval * famnum[i];
        curval = (curval * A) / MOD_BY;
        if (curval < 10)
            curval = 0;
    }
    printf("%ld\n", total_spent);

    curval = value;
    for (int i = 0; i < n; i++) {
        printf("%d\n", curval);
        curval = (curval * A) / MOD_BY;
        if (curval < 10)
            curval = 0;
    }

    return;
}

int main(void)
{
    freopen("coupon.in", "r", stdin);
    freopen("coupon.out", "w", stdout);

    scanf("%ld %lf %ld", &n, &a, &m);
    A = a * MOD_BY;

    for (int i = 0; i < n; i++) {
        scanf("%d", &famnum[i]);
    }

    int curmax = 0;
    int high = m / famnum[0], low = 1, mid;

    while (high > low + 1) {
        mid = (high + low) / 2;

        if (check_in_budget(mid)) {
            curmax = max(curmax, mid);
            low = mid;
        }
        else 
            high = mid;
    }

    if(check_in_budget(high)) curmax = max(curmax, high);

    print_ans(curmax);
    return 0;
}