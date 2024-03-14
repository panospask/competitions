#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct HashString {

    const int MOD = (int)1e9 + 7;
    const int P = 29;

    vector<ll> hash;
    vector<ll> pow;

    void init(string& s) {
        hash.resize(s.size() + 1);
        pow.resize(s.size() + 1);

        hash[0] = 0;
        pow[0] = 1;
        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * P + s[i] - 'a' + 1) % MOD;
            pow[i + 1] = pow[i] * P % MOD;
        }
    }

    int get(int pos, int len) {
        int r = pos + len;

        ll res = hash[r] - hash[pos] * pow[len] % MOD;

        return (res % MOD + MOD) % MOD;
    }
};


int n, m, x;
vector<vector<int>> dp;
string s, t;

HashString s_hash, t_hash;

int longest_common(int i, int j)
{
    int l = 0;
    int r = min(n - i + 1, m - j + 1);

    while (r > l + 1) {
        int mid = (l + r) / 2;

        if (s_hash.get(i, mid) == t_hash.get(j, mid))
            l = mid;
        else
            r = mid;
    }

    return l;
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n >> s >> m >> t >> x;

    s_hash.init(s);
    t_hash.init(t);

    dp.assign(x + 1, vector<int>(n + 1, 0));

    for (int k = 0; k <= x; k++)
        for (int i = 0; i < n; i++) {
            dp[k][i + 1] = max(dp[k][i + 1], dp[k][i]);

            if (k != x) {
                int l = longest_common(i, dp[k][i]);
                dp[k + 1][i + l] = max(dp[k + 1][i + l], dp[k][i] + l);
            }
        }

    if (dp[x][n] == m)
        cout << "YES";
    else
        cout << "NO";
    cout << endl;

    return 0;
}