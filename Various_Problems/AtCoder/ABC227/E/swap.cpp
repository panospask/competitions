#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXK = 465;
const int MAXS = 30;

int N, K;

// dp[i][j][k][s] is the number of ways to obtain a string with
// i Es, j Ks, k Ys ans having done s swaps
long long int dp[MAXS + 1][MAXS + 1][MAXS + 1][MAXK + 1];
vector<int> loc[3];
vector<vector<int>> pref;
string s;

int main(void)
{
    cin >> s >> K;
    K = min(K, MAXK);

    pref.pb({0, 0, 0});
    for (int i = 0; i < s.size(); i++) {
        if (i != 0) {
            pref.pb(pref.back());
        }

        if (s[i] == 'E') {
            pref[i][0]++;
            loc[0].pb(i);
        }
        else if (s[i] == 'K') {
            pref[i][1]++;
            loc[1].pb(i);
        }
        else {
            pref[i][2]++;
            loc[2].pb(i);
        }
    }


    dp[0][0][0][0] = 1;
    for (int i = 0; i <= loc[0].size(); i++) {
        for (int j = 0; j <= loc[1].size(); j++) {
            for (int k = 0; k <= loc[2].size(); k++) {
                for (int s = 0; s <= min(K, MAXK); s++) {
                    if (i != loc[0].size()) {
                        int addcost = max(pref[loc[0][i]][1] - j, 0);
                        addcost += max(pref[loc[0][i]][2] - k, 0);

                        if (addcost <= K) {
                            dp[i + 1][j][k][s + addcost] += dp[i][j][k][s];
                        }
                    }

                    if (j != loc[1].size()) {
                        int addcost = max(pref[loc[1][j]][0] - i, 0);
                        addcost += max(pref[loc[1][j]][2] - k, 0);

                        if (addcost <= K) {
                            dp[i][j + 1][k][s + addcost] += dp[i][j][k][s];
                        }
                    }

                    if (k != loc[2].size()) {
                        int addcost = max(pref[loc[2][k]][1] - j, 0);
                        addcost += max(pref[loc[2][k]][0] - i, 0);

                        if (addcost <= K) {
                            dp[i][j][k + 1][s + addcost] += dp[i][j][k][s];
                        }
                    }
                }
            }
        }
    }

    long long ans = 0;
    for (int s = 0; s <= min(K, MAXK); s++) {
        ans += dp[loc[0].size()][loc[1].size()][loc[2].size()][s];
    }

    printf("%lld\n", ans);

    return 0;
}