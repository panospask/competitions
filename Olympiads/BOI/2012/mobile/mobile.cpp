#include <bits/stdc++.h>

using namespace std;

typedef pair<long long, long long > pl;

int n, l;
vector<pl> transmitters;

bool distance_covers(double x)
{
    double latest_cover = 0;
    for (int i = 0; i < n && latest_cover < l; i++) {
        pl cur = transmitters[i];
        if (cur.second > x)
            continue;

        double k = sqrt(x * x - cur.second * cur.second);

        if (cur.first - k <= latest_cover)
            latest_cover = max(latest_cover, cur.first + k);
    }

    return latest_cover >= l;
}

int main(void)
{
    scanf("%d %d", &n, &l);
    transmitters.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &transmitters[i].first, &transmitters[i].second);

    double l = 0; //distance_covers(l) = false
    double r = 1; //distance_covers(r) = true
    while (!distance_covers(r)) {
        l = r;
        r *= 2;
    }

    for (int i = 0; i < 40; i++) {
        double mid = (l + r) / 2;
        if (distance_covers(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%lf\n", r);
    return 0;
}