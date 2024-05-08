#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

const int INF = 1e9;

typedef pair<int, int> pi;

int N;
vector<int> k;
vector<pi> dp;
vector<bool> useful;
vector<int> prv_useful;
vector<queue<int>> targets;

int main(void)
{
    freopen("police.in", "r", stdin);
    freopen("police.out", "w", stdout);

    scanf("%d", &N);

    k.resize(2 * N);
    targets.resize(N);

    dp.assign(2 * N, mp(INF, INF));
    useful.assign(2 * N, false);
    prv_useful.resize(2 * N, 0);
    for (int i = 0; i < N; i++) {
        scanf("%d", &k[i]);
        k[i + N] = k[i];
    }

    int maxreach = 0;
    for (int i = 0; i < 2 * N; i++) {
        if (i + k[i] > maxreach) {
            maxreach = i + k[i];
            useful[i] = true;
            prv_useful[i] = i;
        }
        else {
            prv_useful[i] = prv_useful[i - 1];
        }
    }

    int ans = INF;
    dp[0] = mp(0, 0);

    for (int i = 0; i < 2 * N; i++) {
        if (!useful[i]) {
            continue;
        }
        if (dp[i].first == INF && i >= N) {
            continue;
        }
        dp[i] = min(dp[i], mp(i, 0));

        targets[dp[i].first].push(i);

        if (i + k[i] < 2 * N) {
            dp[prv_useful[i + k[i]]] =  min(dp[prv_useful[i + k[i]]],  mp(dp[i].first, dp[i].second + 1));
        }

        while (ans > 1 && i + k[i] - targets[dp[i].first].front() >= N) {
            ans = min(ans, dp[i].second + 1 - dp[targets[dp[i].first].front()].second);
            targets[dp[i].first].pop();
        }
    }

    printf("%d\n", ans);

    return 0;
}