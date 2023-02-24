#include <bits/stdc++.h>
#define MAXN 1000

using namespace std;

struct assistant {
    int t, y, z;

    void read_assistant(void) {
        scanf("%d %d %d", &t, &z, &y);
    }
}assistants[MAXN];

int m, n;

int can_inflate_assistant(int min_per_balloon, int rest_after, int rest_time, int total_time)
{
    long long int time_cycle = (min_per_balloon * rest_after) + rest_time;
    long long int total_cycles_performed = total_time / time_cycle;
    long long int time_rem = total_time % time_cycle;

    long long int total_balloons_from_cycles = total_cycles_performed * rest_after;
    long long int extra_balloons = min(time_rem / min_per_balloon, (long long int)rest_after);

    return total_balloons_from_cycles + extra_balloons;
}

bool can_inflate(int time)
{
    int total_inf = 0;
    for (int i = 0; i < n && total_inf < m; i++)
        total_inf += can_inflate_assistant(assistants[i].t, assistants[i].z, assistants[i].y, time);

    return total_inf >= m;
} 

int main(void)
{
    scanf("%d %d", &m, &n);
    for (int i = 0; i < n; i++)
        assistants[i].read_assistant();

    long long int l = -1; // can_inflate(l) = false
    long long int r = 2e9; // can_inflate(r) = true
    while (r > l + 1) {
        long long int mid = ( l + r) / 2;
        if (!can_inflate(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", r);
    int bal_rem = m;
    for (int i = 0; i < n; i++) {
        int cur_remove = min(bal_rem, can_inflate_assistant(assistants[i].t, assistants[i].z, assistants[i].y, r));
        printf("%d ", cur_remove);
        bal_rem -= cur_remove;
    }
    return 0;
}
