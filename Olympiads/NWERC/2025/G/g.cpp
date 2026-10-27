#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

int N;
vector<int> A;
vector<int> pos;

// Left and down arrows by row of the dp table
vector<vector<int>> lft;
vector<vector<int>> down;

int main(void) {
    scanf("%d", &N);

    A.resize(N + 1);
    pos.resize(N + 1);
    lft.resize(N + 1);
    down.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        pos[A[i]] = i;  
    }
    for (int k = 1; k <= N; k++) {
        // Either reach from the left or the right
        int i1 = pos[k];
        int j1 = k - pos[k];

        int j2 = (N + 1) - pos[k];
        int i2 = k - j2;

        if (j1 >= 0) {
            // There is a free transition of (i1 - 1, j1) -> (i1, j1)
            down[i1 - 1].pb(j1);
        }
        if (i2 >= 0) {
            // There is a free transition of (i2, j2 - 1) -> (i2, j2) 
            lft[i2].pb(j2 - 1);
        }
    }

    int ans = 0;
    vector<int> dp(N + 1, INF);
    dp[0] = 0;

    for (int i = 0; i <= N; i++) {
        // Process all the left transitions first in order

        sort(lft[i].begin(), lft[i].end());
        for (auto j : lft[i]) {
            // Which is the best L(not strictly)IS ending in j
            int p = upper_bound(dp.begin(), dp.end(), j) - dp.begin();
            
            // This can now become j + 1
            dp[p] = min(dp[p], j + 1);
        }

        // Now process the down (each one shouldn't affect the others)
        vector<pi> updates;
        for (auto j : down[i]) {
            int p = upper_bound(dp.begin(), dp.end(), j) - dp.begin();

            updates.pb({p, j});
        }
        for (auto [p, j] : updates) {
            dp[p] = min(dp[p], j);
        }
    }

    for (int i = 1; i <= N; i++) {
        if (dp[i] != INF) {
            ans = i;
        }
    }

    printf("%d\n", N - ans);
}