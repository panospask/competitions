#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000
#define MAXK (10e9)
#define MAXX (10e5)

using namespace std;

long long int n, k, x;

long long int calc_distance_covered(long long int topspeed, long long int goalspeed)
{
    // Note that we are on topspeed for two seconds => we must remove one
    long long int distance_accel = ((topspeed) * (topspeed + 1)) / 2;
    long long int distance_decel = ((topspeed - goalspeed + 1) * (topspeed + goalspeed)) / 2;

    long long int total_distance = distance_accel + distance_decel - topspeed;
    return total_distance;
}

int main(void)
{
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);

    scanf("%lld %lld", &k, &n);

    long long int calc_for_only_ac = ceil(((float)-1 + sqrt(1 + (long int)8 * k)) / (float)2);
    for (int t = 0; t < n; t++) {
        scanf("%lld", &x);

        bool only_accel = false;
        if ((x * (x + 1)) / 2 >= k)
            only_accel = true;

        int low = 0;
        int high = k;
        while (low < high && !only_accel) {
            int mid = (low + high) / 2;
            if (mid == low) break;

            if (calc_distance_covered(mid, x) <= k)
                low = mid;
            else
                high = mid;
        }

        int maxspeed = low;
        if (calc_distance_covered(low + 1, x) <= k)
            maxspeed = low + 1;
        
        int dist_covered_from_ups_downs = calc_distance_covered(maxspeed, x);
        
        int ttl_seconds = 0;
        if (!only_accel) {
            int seconds_taken_ac = maxspeed;
            int seconds_taken_dc = maxspeed - x;
            
            int dist_remaining = k - dist_covered_from_ups_downs;
            ttl_seconds = seconds_taken_ac + seconds_taken_dc;
            if (dist_remaining > 0) {
                if (dist_remaining <= maxspeed)
                    ttl_seconds++;
                else 
                    ttl_seconds += 2;
            }
        }
        else {
            ttl_seconds = calc_for_only_ac;
        }

        printf("%d\n", ttl_seconds);
    }

    return 0;
}