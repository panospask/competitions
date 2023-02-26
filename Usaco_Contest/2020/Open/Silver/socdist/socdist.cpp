#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MAXM 100000

using namespace std;

typedef pair<long long int, long long int> ll;

int n, m;
ll segments[MAXM + 5];

bool can_be_x_away(long long int x)
{
    int remcows = n;
    int curseg = 0;
    
    // Place 1 cow at the start of the first segment
    long long int prevpos = segments[curseg].first;
    remcows--;

    while (remcows > 0 && curseg < m) {
        while (curseg < m && segments[curseg].second < prevpos + x)
            curseg++;

        if (curseg == m) break;

        prevpos = max(prevpos + x, segments[curseg].first);
        remcows--;
    }

    return remcows == 0;
}

int main(void)
{
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);
    
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) 
        scanf("%lld %lld", &segments[i].first, &segments[i].second);
    sort(segments, segments + m);

    long long int l = 0; // can_be_x_away(l) = true
    long long int r = 1; // can_be_x_away(r) = false
    while (can_be_x_away(r)) {
        l = r;
        r *= 2;
    }
    while (r > l + 1) {
        auto mid = (l + r) / 2;
        if (can_be_x_away(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%lld\n", l);
    return 0;
}
