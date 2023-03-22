#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXT 5000000

using namespace std;

bool can_reach[MAXT];

long long int t, a, b;

int main(void)
{
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);

    scanf("%lld %lld %lld", &t, &a, &b);
    
    long long int target;
    if (a + b < t)
        target = (long long int)lcm(a, b);
    else 
        target = t;

    for (int i = 0; i <= target && i <= t; i += a) {
        can_reach[i] = true;
    }
    for (int i = 0; i <= target && i <= t; i += b) {
        can_reach[i] = true;
    }

    for (int i = 0; i <= target && i <= t; i++) {
        if (can_reach[i]) {
            if (i + a <= target && i + a <= t)
                can_reach[i + a] = true;
            if (i + b <= target && i + b <= t)
                can_reach[i + b] = true;

            can_reach[i / 2] = true;
        }
    }

    for (int i = 0; i <= target && i <= t; i++) {
        if (can_reach[i]) {
            if (i + a <= target && i + a <= t)
                can_reach[i + a] = true;
            if (i + b <= target && i + b <= t)
                can_reach[i + b] = true;
        }
    }

    int place = t % target;
    if (target == t)
        place = t;
    while (!can_reach[place]) {
        place--;
        t--;
    }

    printf("%lld\n", t);
    return 0;
}