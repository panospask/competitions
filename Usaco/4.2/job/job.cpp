/*
ID: panos.p1
LANG: C++11
TASK: job
*/

#include <bits/stdc++.h>
#define MAXN 30
#define MAXS 20021

int dp[MAXS];
int sum_dp[MAXS];
int latest_delivery[MAXS + 1];
int n, anum, bnum;
int a[MAXN];
int b[MAXN];
int ans1, ans2;
int used[MAXS];

using namespace std;

void calc_first_line(void)
{
    dp[0] = 0;
    int curtime;
    for (int i = 0; i < anum; i++) {
        curtime = a[i];
        for (int t = curtime; t < MAXS; t += curtime) {
            dp[t]++;
        }
    }
    latest_delivery[0] = -1;
    sum_dp[0] = 0;
    int early_sec = -1;
    for (int t = 1; t < MAXS; t++) {
        sum_dp[t] = dp[t] + sum_dp[t-1];
        if (sum_dp[t] >= n && early_sec == -1)
            early_sec = t;
        if (dp[t-1] > 0)
            latest_delivery[t] = t-1;
        else 
            latest_delivery[t] = latest_delivery[t-1];
    }
    ans1 = early_sec;
    if (dp[MAXS - 1] > 0)
        latest_delivery[MAXS] = MAXS - 1;
    else 
        latest_delivery[MAXS] = latest_delivery[MAXS - 1];
}

bool take_largest_task(int t)
{
    // Using binary search for lg n
    // NVM, too much work(segtree implementation)

    while(t > 0) {
        if (dp[t] - used[t] > 0) {
            used[t]++;
            return true;
        }
        t--;
    }

    return false;
}

bool num_over_n(int t)
{
    memset(used, 0, MAXS * sizeof(int));
    int curtime;
    int cursec;
    int ttl_made = 0;
    for (int i = 0; i < bnum && ttl_made < n; i++) {
        curtime = b[i];
        cursec = t - curtime;
             
        while (cursec > 0 && ttl_made < n) {
            if (take_largest_task(cursec)) {
                cursec -= curtime;
                ttl_made++;
            }
            else 
                break;
        }
    }

    if (ttl_made < n)
        return false;
    else 
        return true;
}

void binary_search_second_line(void)
{
    int l = 1, r = MAXS - 1;

    while (l != r) {
        int mid = (l + r) / 2;

        if (num_over_n(mid))
            r = mid;
        else {
            if (mid == l)
                l = r;
            else
                l = mid;
        }
    }

    ans2 = l;
}

int main(void)
{
    freopen("job.in", "r", stdin);
    freopen("job.out", "w", stdout);

    scanf("%d %d %d", &n, &anum, &bnum);
    for (int i = 0; i < anum; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < bnum; i++)
        scanf("%d", &b[i]);

    sort(a, a + anum);
    sort(b, b + bnum);

    calc_first_line();
    binary_search_second_line();

    printf("%d %d\n", ans1, ans2);
    return 0;
}