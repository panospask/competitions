#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int N;
vector<pll> points;
vector<ll> cnt;

int main(void)
{
    scanf("%d", &N);

    cnt.assign(N + 1, 0);
    for (int i = 0; i < N; i++) {
        ll l, r;
        scanf("%lld %lld", &l, &r);
        points.pb(mp(l, 1));
        points.pb(mp(r + 1, -1));
    }
    sort(points.begin(), points.end());

    ll curpos = -1;
    ll curcnt = 0;
    int p = 0;
    while (p < points.size()) {
        cnt[curcnt] += points[p].first - curpos;
        curpos = points[p].first;

        while (p < points.size() && points[p].first == curpos) {
            curcnt += points[p].second;
            p++;
        }
    }

    for (int i = 1; i <= N; i++)
        printf("%lld ", cnt[i]);
    printf("\n");

    return 0;
}