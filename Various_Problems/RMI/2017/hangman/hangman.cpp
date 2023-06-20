#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef __int128_t lll;

struct HashString {

    int n;
    ll MOD = (ll)(1ll << 61) - 1;
    ll P = 31;
    vector<lll> hash;
    vector<lll> pow;

    void init(string& st) {
        n = st.size();
        hash.resize(st.size() + 1);
        pow.resize(st.size() + 1);

        hash[0] = 0;
        pow[0] = 1;
        for (int i = 0; i < st.size(); i++) {
            hash[i + 1] = (hash[i] * P + st[i] - 'a' + 1) % MOD;
            pow[i + 1] = pow[i] * P % MOD;
        }
    }
    void init(string& st, ll m, ll p) {
        MOD = m;
        P = p;
        init(st);
    }

    ll change(int p1, char prv1, char nxt1) {
        int ch1 = nxt1 - prv1;
        lll res = hash.back() + ch1 * pow[n - p1 - 1] % MOD;

        return (res % MOD + MOD) % MOD;
    }
};

int n, k;

vector<bool> removed;

vector<pair<pair<ll, ll>, int>> all;

vector<HashString> hashes;
vector<HashString> hashes2;
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
    hashes2.resize(n);
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
        hashes2[i].init(words[i], 1e9 + 7, 53);

        for (int p1 = 0; p1 < k; p1++) {
            for (int l1 = 0; l1 < 26; l1++) {
                ll r1 = hashes[i].change(p1, words[i][p1], l1 + 'a');
                ll r2 = hashes2[i].change(p1, words[i][p1], l1 + 'a');

                all.push_back(mp(mp(r1, r2), i));
            }
        }
    }

    pair<ll, ll> prv_num = mp(-1, -1);
    int prv_id = -1;
    for (auto& v : all) {
        if (v.f == prv_num && v.s != prv_id) {
            removed[prv_id] = removed[v.s] = true;
        }

        assert(v.f.f >= 0 && v.f.s >= 0);
        prv_num = v.f;
        prv_id = v.s;
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