#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int N, s1, s2;
vector<tuple<int, int, int, int>> quests;

// dp[i][e1][e2]: Using the first i quests, what is the minimum cost to get e1 experience on the first level and e2 on the second level?
vector<vector<ll>> dp;
vector<vector<ll>> nxt;

void minimize(ll& a, ll b)
{
    if (a > b) {
        a = b;
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &s1, &s2);

    dp.assign(s1 + 1, vector<ll>(s2 + 1, INF));
    quests.resize(N);
    dp[0][0] = 0;

    for (int i = 0; i < N; i++) {
        int x, y, t, r;
        scanf("%d %d %d %d", &x, &t, &y, &r);

        quests[i] = make_tuple(x, t, y, r);
    }
    sort(quests.begin(), quests.end());

    for (int i = 0; i < N; i++) {
        int x, t, y, r;
        tie(x, t, y, r) = quests[i];

        nxt.assign(s1 + 1, vector<ll>(s2 + 1, INF));

        for (int e1 = 0; e1 <= s1; e1++) {
            for (int e2 = 0; e2 <= s2; e2++) {
                if (dp[e1][e2] == INF) {
                    continue;
                }

                minimize(nxt[e1][e2], dp[e1][e2]);

                if (e1 + x <= s1) {
                    minimize(nxt[e1 + x][e2], dp[e1][e2] + t);
                }
                else if (e1 != s1) {
                    int rem = e1 + x - s1;
                    minimize(nxt[s1][min(e2 + rem, s2)], dp[e1][e2] + t);
                }
                minimize(nxt[e1][min(s2, e2 + y)], dp[e1][e2] + r);
            }
        }

        swap(dp, nxt);
    }

    if (dp[s1][s2] == INF) {
        printf("-1\n");
    }
    else {
        printf("%lld\n", dp[s1][s2]);
    }

    return 0;
}