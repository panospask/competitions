#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int N;

int main(void) {
    cin >> N;

    vector<int> cnt(3, 0);
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        if (c == 'r') {
            cnt[0]++;
        }
        else if (c == 'b') {
            cnt[1]++;
        }
        else {
            cnt[2]++;
        }
    }
    
    ld ans = 0;
    sort(cnt.begin(), cnt.end());
    reverse(cnt.begin(), cnt.end());

    // For sure turn all the "worst" lights to either one
    ans += (ld)cnt[2] * 1.5;

    vector<vector<ld>> dp(cnt[2] + 1, vector<ld>(cnt[2] + 1, 0));
    dp[0][0] = 1;
    for (int v = 1; v <= cnt[2]; v++) {
        for (int j = 0; j <= v; j++) {
            dp[v][j] = dp[v - 1][j] / 2;
            if (j) {
                dp[v][j] += dp[v - 1][j - 1] / 2;
            }
        }
    }

    for (int j = 0; j <= cnt[2]; j++) {
        // How many turned into cnt[0]

        int v1 = cnt[0] + j;
        int v2 = cnt[1] + (cnt[2] - j);

        ans += 3 * min(v1, v2) * dp[cnt[2]][j];
    }

    cout << fixed << setprecision(8) << ans << endl;
}