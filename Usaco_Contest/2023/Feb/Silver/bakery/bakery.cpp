#include <bits/stdc++.h>
#define MAXN 100
#define mp make_pair

using namespace std;

long long int a[MAXN + 2], b[MAXN + 2], c[MAXN + 2];
long long int cookietime, muffintime;
int n;
int t;

bool intime(long long int cookie_points, long long int muffin_points, int cow)
{
    return cookie_points * a[cow] + muffin_points * b[cow] <= c[cow];
}

pair<int, int> find_cookie_range(long long int z, int cow)
{
    long long int min_x = max(1ll, z - muffintime);
    long long int max_x = min(cookietime, z-1);

    if (a[cow] > b[cow]) {
        max_x = min(max_x, (c[cow] - z * b[cow]) / (a[cow] - b[cow]) );
    }
    else if (a[cow] < b[cow]) {
        min_x = max(min_x, (c[cow] - z * b[cow]) / (a[cow] - b[cow]) + (((c[cow] - z * b[cow]) % (a[cow] - b[cow])) != 0));
    }
    else {
        if (c[cow] < z * b[cow])
            return mp(-1, -1);
    }


    if (min_x > max_x)
        return mp(-1, -1);
    return mp(min_x, max_x);
}

bool intersect(long int a1, long int b1, long int a2, long int b2)
{
    return a1 <= b2 && a2 <= b1;
}

// Check if total x time points(allocated to cookie and muffin together) are enough
bool service(long long int x)
{
    int ttl_start = 0;
    int ttl_end = INT_MAX;
    for (int i = 0; i < n; i++) {
        pair<int, int> cur = find_cookie_range(x, i);

        if (!intersect(ttl_start, ttl_end, cur.first, cur.second))
            return false;

        ttl_start = max(ttl_start, cur.first);
        ttl_end = min(ttl_end, cur.second); 
    }

    return true;
}

int main(void)
{
    // freopen("bakery.in", "r", stdin);
    // freopen("bakery.out", "w", stdout);

    scanf("%d", &t);
    for (int cases = 0; cases < t; cases++) {
        scanf("%d %lld %lld", &n, &cookietime, &muffintime);
        for (int i = 0; i < n; i++)
            scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);

        long long int l = 2; // service(l) = true
        long long int r = cookietime + muffintime + 1; // service(r) = false
        while (r > l + 1) {
            auto m = (l + r) / 2;
            if (!service(m))
                r = m;
            else 
                l = m;
        }

        printf("%lld\n", cookietime + muffintime - l);
    }

    return 0;
}