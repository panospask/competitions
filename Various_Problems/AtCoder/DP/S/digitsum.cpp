#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;
const int MAXP = 10000;
const int MAXD = 100;

// #of numbers int pos and below such that their digsum mod D is d
int D;
vector<int> number;
int dp[MAXP + 1][MAXD][2];


int calculate_dp(int pos = MAXP, int curd = 0, bool smaller = false)
{
    if (pos == -1) {
        return curd == 0;
    }
    if (dp[pos][curd][smaller] != -1) {
        return dp[pos][curd][smaller];
    }

    dp[pos][curd][smaller] = 0;

    int v = number[pos];

    for (int l = 0; l < 10; l++) {
        int search = curd - l;
        search = (search % D + D) % D;

        int res = 0;
        if (l < v) {
            res = calculate_dp(pos - 1, search, true);
        }
        else if (l == v) {
            res = calculate_dp(pos - 1, search, smaller);
        }
        else {
            if (smaller)
                res = calculate_dp(pos - 1, search, smaller);
        }

        dp[pos][curd][smaller] += res;
        if (dp[pos][curd][smaller] > MOD)
            dp[pos][curd][smaller] -= MOD;
    }

    return dp[pos][curd][smaller];
}

int main(void)
{
    string s;
    cin >> s;
    cin >> D;

    number.resize(s.size());
    for (int i = 0; i < s.size(); i++)
        number[i] = s[i] - '0';
    reverse(number.begin(), number.end());

    memset(dp, -1, sizeof(dp));

    int ans = calculate_dp(number.size() - 1) - 1;
    cout << ans << endl;

    return 0;
}