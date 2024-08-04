#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ll;

const int MAXDIGITS = 16;
const int DIGCNT = 10;
const ll INF = ULLONG_MAX;

ll A, B;
vector<int> targetnum;


/* dp[pos][under]:
 * Digit sum of numbers after reaching position p
 * 
 * cnt[pos][under]:
 * Count of numbers after reaching position p
 * 
 * under is a boolean variable on weather we have gone under the target or not
 */
ll dp[MAXDIGITS + 1][2];
ll cnt[MAXDIGITS + 1][2];

void calculate_dp(int pos, bool under)
{
    if (dp[pos][under] != INF) {
        return;
    }

    if (pos == targetnum.size()) {
        // Only 1 number left, the null number
        
        dp[pos][under] = 0;
        cnt[pos][under] = 1;
        return;
    }

    dp[pos][under] = cnt[pos][under] = 0;
    for (int d = 0; d < DIGCNT; d++) {
        if (d > targetnum[pos] && !under) {
            continue;
        }

        bool new_under = under || (d < targetnum[pos]);
        calculate_dp(pos + 1, new_under);

        cnt[pos][under] += cnt[pos + 1][new_under];
        
        dp[pos][under] += dp[pos + 1][new_under] + (ll)d * cnt[pos + 1][new_under];
    }

    return;
}

void make_target(ll t)
{
    targetnum.clear();

    while (t) {
        targetnum.push_back(t % 10);
        t /= 10;
    }

    reverse(targetnum.begin(), targetnum.end());
}

void clear_dp(void)
{
    for (int i = 0; i <= MAXDIGITS; i++) {
        for (int j = 0; j < 2; j++) {
            dp[i][j] = INF;
        }
    }
}

void solve(void)
{
    cin >> A >> B;

    clear_dp();
    make_target(B);
    calculate_dp(0, false);

    ll ans = dp[0][false];

    if (A) {
        clear_dp();
        make_target(A - 1);
        calculate_dp(0, false);
        ans -= dp[0][false];
    }

    cout << ans << endl;

    return;
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