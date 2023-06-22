#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef __int128_t lll;

struct HashString {

    int n;
    const ll MOD = (ll)(1ll << 61) - 1;
    const ll P = 31;
    vector<lll> hash;
    vector<lll> pow;

    void init(string& s) {
        n = s.size();
        hash.resize(s.size() + 1);
        pow.resize(s.size() + 1);

        hash[0] = 0;
        pow[0] = 1;
        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * P + s[i] - 'a' + 1) % MOD;
            pow[i + 1] = pow[i] * P % MOD;
        }
    }

    ll remove(int p1, char c1, int p2, char c2) {
        lll res = hash.back() - (c1 - 'a' + 1) * pow[n - p1 - 1] % MOD;
        res = res - (c2 - 'a' + 1) * pow[n - p2 -1] % MOD;

        return (res % MOD + MOD) % MOD;
    }
};

int n, k;

vector<bool> removed;

vector<pair<ll, int>> all;
vector<HashString> hashes;
vector<string> words;

bool check(int i, int j)
{
    int diff = 0;
    for (int k = 0; k < words[i].size(); k++)
        diff += words[i][k] != words[j][k];

    return diff <= 2;
}

void solve(void)
{
    hashes.clear();
    words.clear();
    all.clear();

    cin >> n >> k;

    removed.assign(n, false);
    hashes.resize(n);
    removed.assign(n, false);
    words.resize(n);

    if (n < 2000) {
        for (int i = 0; i < n; i++) {
            cin >> words[i];
            for (int j = 0; j < i; j++) {
                if (check(i, j)) {
                    removed[i] = removed[j] = true;
                }
            }
        }

        for (int i = 0; i < n; i++)
            cout << (int)removed[i];
        cout << endl;
        return ;
    }

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        hashes[i].init(words[i]);
    }
    for (int a = 0; a < k; a++)
        for (int b = a + 1; b < k; b++) {
            all.clear();
            for (int i = 0; i < n; i++) {
                ll res = hashes[i].remove(a, words[i][a], b, words[i][b]);
                all.push_back(mp(res, i));
            }
            sort(all.begin(), all.end());

            for (int i = 0; i < all.size() - 1; i++)
                if (all[i].first == all[i + 1].first) {
                    removed[all[i].second] = removed[all[i + 1].second] = true;
                }
        }


    for (int i = 0; i < n; i++)
        cout << (int)removed[i];
    cout << endl;
}

int main(void)
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}