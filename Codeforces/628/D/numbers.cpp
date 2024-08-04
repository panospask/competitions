#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXDIGITS = 2000;
const int MAXM = 2000;
const int DIGITS = 10;

int M, D;
string A, B;
vector<int> targetnum;
vector<int> pwr;

/* dp[pos][rem][under]:
 * The number of d-magic numbers with remainder rem when divided by m
 * under is a boolean variable denoting if we have gone under the target
 * starting is a boolean variable denoting if we have placed the first nonzero digit
 */
ll dp[MAXDIGITS + 1][MAXM][2];

inline void mod(ll& a)
{
    if (a > MOD) {
        a -= MOD;
    }
}

void calculate_dp(int pos, int rem, bool under)
{
    if (dp[pos][rem][under] != -1) {
        return;
    }

    if (pos == targetnum.size()) {
        dp[pos][rem][under] = (rem == 0);
        return;
    }

    dp[pos][rem][under] = 0;
    for (int d = 0; d < DIGITS; d++) {
        bool new_under = under || (d < targetnum[pos]);

        if (pos == 0 && d == 0) {
            // A and B have same digits so we don't care about lower digits
            continue;
        }
        if (!new_under && d > targetnum[pos]) {
            continue;
        }
        if ((pos + 1) % 2 != 0 && d == D) {
            continue;
        }
        if ((pos + 1) % 2 == 0 && d != D) {
            continue;
        }

        int add = d * pwr[targetnum.size() - 1 - pos] % M;
        calculate_dp(pos + 1, (rem + add) % M, new_under);
        dp[pos][rem][under] += dp[pos + 1][(rem + add) % M][new_under];
        mod(dp[pos][rem][under]);
    }
}

void clear(void)
{
    for (int pos = 0; pos <= MAXDIGITS; pos++) {
        for (int rem = 0; rem < M; rem++) {
            for (int p1 = 0; p1 < 2; p1++) {
                dp[pos][rem][p1] = -1;
            }
        }
    }
}

void make_target(string& s)
{
    targetnum.resize(s.size());
    pwr.resize(s.size());
    for (int i = 0; i < s.size(); i++) {
        targetnum[i] = s[i] - '0';
        pwr[i] = !i ? 1 : pwr[i - 1] * 10 % M;
    }
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> M >> D >> A >> B;

    ll ans = 0;

    clear();
    make_target(B);
    calculate_dp(0, 0, false);
    ans += dp[0][0][false];

    clear();
    make_target(A);
    calculate_dp(0, 0, false);
    ans -= dp[0][0][false];

    // If A is d-magic then add 1 to the answer
    bool good = true;
    int rem = 0;
    for (int i = 0; i < targetnum.size(); i++) {
        if ((i + 1) % 2 == 0 && targetnum[i] != D) {
            good = false;
        }
        if ((i + 1) % 2 != 0 && targetnum[i] == D) {
            good = false;
        }
        rem += pwr[targetnum.size() - 1 - i] * targetnum[i] % M;
        rem %= M;
    }
    good = good && !rem;
    ans += good;

    ans = (ans % MOD + MOD) % MOD;
    printf("%lld\n", ans);

    return 0;
}