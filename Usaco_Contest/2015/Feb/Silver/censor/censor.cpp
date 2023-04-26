#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;

const int MOD = ((int)1e9 + 7);
const int B = 29;

string s, t;
string res;
vector<ll> r_hash(1, 0);
vector<ll> r_pow(1, 1);
vector<ii> del;

ll next_hash(ll h, ll c)
{
    return (h * B + c) % MOD;
}

int main(void)
{
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin >> s >> t;

    // Hash t
    ll t_hash = 0;
    for (int i = 0; i < t.size(); i++)
        t_hash = next_hash(t_hash, t[i] - 'a');

    int curp = 0;
    for (int i = 0; i < s.size(); i++) {
        res.push_back(s[i]);
        r_hash.push_back(next_hash(r_hash.back(), s[i] - 'a'));
        r_pow.push_back(r_pow.back() * B % MOD);

        if (res.size() >= t.size()) {
            ll sub = r_hash[res.size() - t.size()] * r_pow[t.size()] % MOD;
            ll r = r_hash.back() - sub;
            r = (r + MOD) % MOD;

            if (r == t_hash) {
                r_hash.resize(r_hash.size() - t.size());
                r_pow.resize(r_pow.size() - t.size());
                res.resize(res.size() - t.size());
            }
        }
    }

    cout << res << endl;
    return 0;
}