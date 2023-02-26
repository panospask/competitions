#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000 

using namespace std;

int machines[MAXN + 5];
double pref_sum[MAXN + 5];
double min_up_to[MAXN + 5];
int n, k;

bool can_have_avg(double x)
{
    pref_sum[0] = machines[0] - x;
    min_up_to[0] = pref_sum[0];
    for (int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i-1] + machines[i] - x;
        min_up_to[i] = min(min_up_to[i-1], pref_sum[i]);
    }

    for (int i = 1; i < n - 1; i++) {
        if (pref_sum[n - 1] - pref_sum[i] + min_up_to[i - 1] <= 0)
            return true;
    }

    return false;
}

int main(void)
{
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) 
        scanf("%d", &machines[i]);

    double l = 0; // can_have_avg(l) = false
    double r = 10000; // can_have_avg(r) = true
    for (int i = 0; i < 80; i++) {
        auto mid = (l + r) / 2;
        if (can_have_avg(mid))
            r = mid;
        else 
            l = mid;
    } 

    printf("%.3lf\n", r);
    return 0;
}