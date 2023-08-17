#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct Event {
    int profit_change;
    int core_change;
    int rate;

    bool operator < (Event b) {
        if (this->rate == b.rate)
            return this->core_change > b.core_change;

        return this->rate > b.rate;
    }
};

int N, M;

// dp[i][j]: After the first i events (sorted in clock rate), maximum profit with at least j cores left over
vector<ll> dp;
vector<ll> prv;
vector<Event> events;

int main(void)
{
    scanf("%d", &N);


    for (int i = 0; i < N; i++) {
        int c, f, v;
        scanf("%d %d %d", &c, &f, &v);

        events.pb({-v, c, f});
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int c, f, v;
        scanf("%d %d %d", &c, &f, &v);

        events.pb({v, -c, f});
    }

    sort(events.begin(), events.end());

    prv.assign(N * 50  + 1, -INF);
    dp.resize(N * 50 + 1);

    prv[0] = 0;
    for (int i = 1; i <= N + M; i++) {
        int cores = events[i - 1].core_change;
        int v = events[i - 1].profit_change;
        for (int j = 0; j <= N * 50; j++) {
            dp[j] = prv[j];
            if (j - cores >= 0 && j - cores <= N * 50 && prv[j - cores] != -INF)
                dp[j] = max(dp[j], prv[j - cores] + v);
        }

        swap(dp, prv);
    }

    ll ans = 0;
    for (int i = 0; i <= N * 50; i++)
        ans = max(ans, prv[i]);

    printf("%lld\n", ans);
}