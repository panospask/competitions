#include <bits/stdc++.h>

using namespace std;

int n ,d, m;
vector<int> jobs;

bool can_complete(int x)
{
    int cur_day = 0;
    vector<int> jobs_at = jobs;
    for (int i = 0; i < n; i++) {
        if (i - cur_day > d)
            return false;

        int avail = x;
        while (avail > 0 && cur_day <= i) {
            int rm = min(avail, jobs_at[cur_day]);
            avail -= rm;
            jobs_at[cur_day] -= rm;
            while (cur_day <= i && jobs_at[cur_day] == 0)
                cur_day++;
        }
    }

    return true;
}

int main(void)
{
    scanf("%d %d %d", &n, &d, &m);
    jobs.assign(n, 0);
    for (int i = 0; i < m; i++) {
        int day;
        scanf("%d", &day);
        day--;

        jobs[day]++;
    }

    int l = 0;
    int r = m;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_complete(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);
    return 0;
}