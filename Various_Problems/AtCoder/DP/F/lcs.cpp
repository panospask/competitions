#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N, M;
string s, t;
vector<vector<int>> dp;
vector<vector<int>> prv;

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> s >> t;
    N = s.size();
    M = t.size();

    dp.resize(N + 1, vector<int>(M + 1));
    prv.resize(N + 1, vector<int>(M + 1));
    dp[0][0] = 0;
    prv[0][0] = -1;
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++) {
            if (i != N && dp[i + 1][j] < dp[i][j]) {
                dp[i + 1][j] = dp[i][j];
                prv[i + 1][j] = prv[i][j];
            }
            if (j != M && dp[i][j + 1] < dp[i][j]) {
                dp[i][j + 1] = dp[i][j];
                prv[i][j + 1] = prv[i][j];
            }
            if (i != N && j != M && s[i] == t[j] && dp[i + 1][j + 1] < dp[i][j] + 1) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
                prv[i + 1][j + 1] = i;
            }
        }

    string ans;
    int i = N, j = M;
    for (int v = prv[i][j]; dp[i][j] > 0 ; v = prv[i][j]) {
        ans.push_back(s[v]);
        i = v;
        j--;
        while (t[j] != s[i])
            j--;
    }

    reverse(ans.begin(), ans.end());
    cout << ans << endl;

    return 0;
}