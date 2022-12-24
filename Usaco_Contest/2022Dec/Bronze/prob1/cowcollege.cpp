#include <bits/stdc++.h>
#define MAXN (int)(10e5+10)
#define MAXC (int)(10e6+10)

using namespace std;

int n;
int maxprice[MAXN];

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &maxprice[i]);
    sort(maxprice, maxprice + n);

    long long int max_money = 0;
    int max_charge = 0;
    long long int cur_money;
    int cur_charge;

    for (int i = 0; i < n; i++) {
        int cur_charge = maxprice[i];
        cur_money = (long long int)cur_charge * (n - i);
        if (cur_money > max_money) {
            max_money = cur_money;
            max_charge = cur_charge;
        }
    }

    printf("%lld %d\n", max_money, max_charge);
    return 0;
}