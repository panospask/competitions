#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
#define pb push_back

using namespace std;

const int INF = 1e6;

typedef long long ll;

int N, M;
vector<vector<bool>> lines;
vector<bool> done;

vector<vector<vector<int>>> groups;
vector<vector<int>> dp;

int main(void) {
    scanf("%d %d", &N, &M);

    lines.resize(M);
    groups.resize(1 << N);
    done.assign(1 << N, false);

    for (int i = 0; i < M; i++) {
        int n;
        scanf("%d", &n);

        lines[i].assign(N, false);
        for (int j = 0; j < n; j++) {
            int c;
            scanf("%d", &c);
            lines[i][c] = true;
        }
    }

    if (M == 1) {
        printf("0\n");
        return 0;
    }

    done[0] = true;
    groups[0].pb({});
    for (int i = 0; i < M; i++) {
        groups[0][0].pb(i);
    }

    for (int mask = 0; mask < (1 << N); mask++) {
        for (int i = 0; i < N; i++) {
            if (done[mask ^ (1 << i)]) {
                continue;
            }

            done[mask ^ (1 << i)] = true;
            for (auto& g : groups[mask]) {
                vector<int> nxt[2];
                for (auto& p : g) {
                    nxt[lines[p][i]].pb(p);
                }

                for (int s = 0; s < 2; s++) {
                    if (nxt[s].size() < 2) {
                        continue;
                    }
                    groups[mask + (1 << i)].pb(nxt[s]);
                }
            }
        }
    }

    if (groups[(1 << N) - 1].size() > 0) {
        printf("not possible\n");
        return 0;
    }

    dp.assign(1 << N, vector<int>());
    int ans = INF;
    for (int mask = (1 << N) - 1; mask >= 0; mask--) {
        dp[mask].assign(groups[mask].size(), INF);

        vector<int> idx(M, -1);
        for (int g = 0; g < groups[mask].size(); g++) {
            for (auto p : groups[mask][g]) {
                idx[p] = g;
            }
        }

        for (int i = 0; i < N; i++) {
            if (CHECK_BIT(mask, i)) {
                continue;
            }

            vector<int> opt(groups[mask].size(), 0);
            
            int nxt = mask + (1 << i);
            for (int g = 0; g < groups[nxt].size(); g++) {
                // Previous group
                int prv = idx[groups[nxt][g][0]];
                opt[prv] += dp[nxt][g];
            }

            for (int g = 0; g < groups[mask].size(); g++) {
                dp[mask][g] = min(dp[mask][g], (int)groups[mask][g].size() + opt[g]);
            }
        }

        if (mask == 0) {
            ans = min(ans, dp[mask][0]);
        }
    }

    printf("%lf\n", (double)ans / M);

    return 0;
}