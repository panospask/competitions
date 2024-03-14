#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct StringHash {

    const int MOD = ((int)1e9 + 7);
    const int P = 31;

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

    int get(int l, int len) {
        int r = l + len - 1;

        ll res = hash[r + 1] - hash[l] * pow[len] % MOD;

        return (res + MOD) % MOD;
    }
};

int n;
string s;

StringHash h, h_rev;
vector<vector<int>> d;
vector<int> k_pals;

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> s;
    n = s.size();
    h.init(s);
    reverse(s.begin(), s.end());
    h_rev.init(s);
    d.assign(n, vector<int>(n + 1, 0));

    k_pals.assign(n + 1, 0);
    // The empty string is no palindrome

    for (int len = 1; len <= n; len++)
        for (int l = 0; l <= n - len; l++) {
            int r = l + len - 1;

            int deg = 0;
            if (h.get(l, len / 2) == h_rev.get(n - 1 - r, len / 2))
                deg = d[l][len / 2] + 1;

            d[l][len] = deg;
            k_pals[deg]++;
        }

    for (int i = n - 1; i >= 0; i--)
        k_pals[i] += k_pals[i + 1];

    for (int i = 1; i <= n; i++)
        cout << k_pals[i] << ' ';
    cout << endl;

    return 0;
}