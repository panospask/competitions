#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<long long int, long long int> ll;
ll startingcows[MAXN + 2];
ll endingcows[MAXN + 2];
int fin_array[MAXN + 2];
long long int dp[MAXN + 2];
int n, t;

bool stabcomp(ll a, ll b)
{
    if (a.first != b.first)
        return a.first < b.first;

    return a.second > b.second;
}

int main(void)
{
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);

    scanf("%d %d", &n, &t);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &startingcows[i].first, &startingcows[i].second);

        startingcows[i].second = startingcows[i].first + startingcows[i].second * t;
    }
    sort(startingcows, startingcows + n, stabcomp);
    
    for (int i = 0; i <= n + 1; i++)
        dp[i] = LONG_LONG_MIN;
    dp[0] = LONG_LONG_MAX;

    for (int i = 1; i <= n; i++) {
        auto curval = startingcows[i-1].second;

        int l = 0;
        int r = n + 1;
        while (r > l + 1) {
            auto mid = (l + r) / 2;
            if (dp[mid] >= curval)
                l = mid;
            else 
                r = mid;
        }

        dp[l+1] = curval;
    }

    int ans = 0;
    while (dp[ans + 1] != LONG_LONG_MIN)
        ans++;
    printf("%d\n", ans);
    return 0;
}