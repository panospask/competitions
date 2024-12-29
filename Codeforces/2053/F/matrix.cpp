#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M, K;

ll base = 0;

ll good;

vector<vector<int>> grid;
vector<int> blanks;

// cnt[i][v]: NUmber of occurences of v in row i
vector<map<int, int>> cnt;

// dp[i][j]: Maximum beauty of the first i + 1 rows when in
// the last row the blanks are filled as j (ignoring the beauty that comes from initial elements from both sides)
vector<map<int, ll>> dp;

// max(dp[i][j]) iterating over j
vector<ll> opt;

//values[i]: The set of all non blank values that appear in i
vector<set<int>> values;

//rows[v]: The set of rows in which v appears
vector<set<int>> rows; 

//pref[r]: sum of blanks[i] * blanks[i - 1] for each i in [1, r]
vector<ll> pref;

ll calculate_dp(int i, int j)
{
    // dp[i][j] only appears in rows where j appears
    // and in rows where j appears in the previous row

    auto it = rows[j].upper_bound(i);
    it--;

    // The last time dp of j appears is as dp[r][j]
    int r = min(*it + 1, i);

    return max(good, dp[r][j] + pref[i] - pref[r]);
}

void solve(void)
{
    scanf("%d %d %d", &N, &M, &K);

    grid.assign(N, vector<int>(M, 0));
    cnt.assign(N, map<int, int>());
    blanks.assign(N, 0);
    pref.assign(N, 0);

    rows.assign(M * N, set<int>());
    values.assign(N, set<int>());

    good = 0;

    for (int v = 0; v < K; v++) {
        rows[v].insert(-1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &grid[i][j]);

            grid[i][j]--;
            if (grid[i][j] != -2) {
                cnt[i][grid[i][j]]++;
                rows[grid[i][j]].insert(i);
                values[i].insert(grid[i][j]);
            }
            else {
                blanks[i]++;
            }
        }
    }

    opt.assign(N, 0);
    dp.assign(N, map<int, ll>());
    base = 0;

    for (int i = 1; i < N; i++) {
        // Process row i

        // First calculate the base value
        for (auto [col, times] : cnt[i]) {
            base += (ll)times * cnt[i - 1][col];
        }

        // Calculate the optimal value to place in the blanks of row (i-1), if we ignore the blanks of row i
        ll best = opt[i - 1];

        // We only need to consider values that appear in row i (and of course the global best of row i - 1)
        for (auto v : values[i]) {
            best = max(best, calculate_dp(i - 1, v) + (ll)cnt[i][v] * blanks[i - 1]);
        }

        // For the actual dp, we only need to consider values that appear either in row i or in row i - 1
        set<int> total = values[i - 1];
        opt[i] = (ll)blanks[i] * blanks[i - 1] + opt[i - 1];
        total.insert(values[i].begin(), values[i].end());
        for (auto v : total) {
            dp[i][v] = max(best + (ll)cnt[i - 1][v] * blanks[i],
                        calculate_dp(i - 1, v) + (ll)cnt[i - 1][v] * blanks[i] + (ll)cnt[i][v] * blanks[i - 1] + (ll)blanks[i] * blanks[i - 1]);

            opt[i] = max(opt[i], dp[i][v]);
        }

        // Update pref[i]
        pref[i] = pref[i - 1] + (ll)blanks[i - 1] * blanks[i];

        // Update good
        // Why put best here?
        good = max(best, good + (ll)blanks[i] * blanks[i - 1]);
    }

    ll ans = 0;
    for (int v = 0; v < K; v++) {
        ans = max(ans, calculate_dp(N - 1, v));
    }

    printf("%lld\n", ans + base);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}