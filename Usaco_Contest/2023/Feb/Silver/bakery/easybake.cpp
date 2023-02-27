#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

long long int a[MAXN + 5], b[MAXN + 5];
long long int c[MAXN + 5];
int t, n, t_c, t_m;

long long int calc_muffin_time(int participant, int cookie_time)
{
    long long int total_muffin_time = c[participant] - a[participant] * cookie_time;

    return total_muffin_time / b[participant];
}

int main(void)
{
    // freopen("bakery.in", "r", stdin);
    // freopen("bakery.out", "w", stdout);

    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        scanf("%d %d %d", &n, &t_c, &t_m);
        for (int i = 0; i < n; i++)
            scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);

        long long int minans = INT_MAX;
        for (int reduce_c = 0; reduce_c < t_c; reduce_c++) {
            int new_c_time = t_c - reduce_c;
            // Given cookie time, calc how much time the muffins should take

            long long int min_muffin_time = INT_MAX;
            for (int i = 0; i < n; i++)
                min_muffin_time = min(min_muffin_time, calc_muffin_time(i, new_c_time));

            long long int muffin_cost;
            if (min_muffin_time >= t_m)
                muffin_cost = 0;
            else if (min_muffin_time <= 0)
                muffin_cost = INT_MAX;
            else    
                muffin_cost = t_m - min_muffin_time;

            minans = min(minans, reduce_c + muffin_cost);
        }

        printf("%lld\n", minans);
    }

    return 0;
}