#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(v, p) (v & (1<<p))

using namespace std;

int n, b;

vector<vector<int>> s;
vector<vector<pair<int, int>>> bonuses;

vector<int> dp;

int main(void)
{
    freopen("dec.in", "r", stdin);
    freopen("dec.out", "w", stdout);

    scanf("%d %d", &n, &b);
    bonuses.resize(n);
    s.resize(n, vector<int>(n));

    for (int i = 0; i < b; i++) {
        int k, p, a;
        scanf("%d %d %d", &k, &p, &a);
        k--;
        bonuses[k].pb(mp(p, a));
    }

    for (int i = 0; i < n; i++) {
        sort(bonuses[i].begin(), bonuses[i].end());
        for (int j = 0; j < n; j++)
            scanf("%d", &s[i][j]);
    }

    dp.resize(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        int nxtev = __builtin_popcount(i);
        for (int j = 0; j < n; j++) {
            if (!CHECK_BIT(i, j)) {
                int v = dp[i] + s[j][nxtev];
                int curp = 0;
                while (curp < bonuses[nxtev].size() && v >= bonuses[nxtev][curp].first)
                    v += bonuses[nxtev][curp++].second;

                dp[i + (1 << j)] = max(dp[i + (1 << j)], v);
            }
        }
    }

    printf("%d\n", dp[(1 << n) - 1]);

    return 0;
}