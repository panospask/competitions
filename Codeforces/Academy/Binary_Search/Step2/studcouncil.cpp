#include <bits/stdc++.h>
#define MAXN 50
#define MAXK 20

using namespace std;

int k, n;
long long int cap[MAXN + 5];

bool can_build(long long int x)
{
    long long int studs_to_place = (long long int)x * k;
    for (int i = 0; i < n && studs_to_place > 0; i++) {
        studs_to_place -= min(cap[i], x);
    }
    return studs_to_place <= 0;
}

int main(void)
{
    scanf("%d %d", &k, &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &cap[i]);
    sort(cap, cap + n);

    long long int l = 0; // can_build(l) = true
    long long int r = 1; // can_build(r) = false
    while (can_build(r)) {
        l = r;
        r *= 2;
    }

    while (r > l + 1) {
        long long int mid = (r + l) / 2;
        if (can_build(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", l);
    return 0;
}