#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int M1 = (int)1e9 + 7;
const int P1 = 31;

struct StringHash {

    int MOD;
    int P;
    vector<ll> hash;
    vector<ll> pow;

    void init(int m, int p, string& st) {
        MOD = m;
        P = p;

        hash.resize(st.size() + 1);
        pow.resize(st.size() + 1);

        hash[0] = 0;
        pow[0] = 1;
        for (int i = 0; i < st.size(); i++) {
            hash[i + 1] = (hash[i] * P + st[i] - 'a' + 1) % MOD;
            pow[i + 1] = pow[i] * P % MOD;
        }
    }

    int getHash(int l, int r) {
        ll res = hash[r + 1] - hash[l] * pow[r - l + 1] % MOD;
        return (res % MOD + MOD) % MOD;
    }

    int total(void) {
        return hash.back();
    }
};

int n;
string s, t;

int first_oc;
int sec_oc;
int idx_sec;
vector<bool> sign;

StringHash t_hash;

bool check_combo(int l1, int l2)
{
    if (l1 == 0 || l2 == 0)
        return false;

    int h1 = t_hash.getHash(0, l1 - 1);
    int h2 = t_hash.getHash(idx_sec * l1, idx_sec * l1 + l2 - 1);

    assert(min(h1, h2) >= 0 && max(h1, h2) < M1);

    if (h1 == h2)
        return false;

    int curp = 0;
    int i = 0;
    int l = 0;
    bool  good = true;
    while (good && i < sign.size()) {
        if (sign[i] == 0) {
            // Check r1
            if (h1 == t_hash.getHash(l, l + l1 - 1)) {
                l += l1;
                i++;
            }
            else {
                good = false;
            }
        }
        else {
            // Check r2
            if (h2 == t_hash.getHash(l, l + l2 - 1)) {
                l += l2;
                i++;
            }
            else {
                good = false;
            }
        }
    }

    return good;
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> s >> t;
    sign.resize(s.size());

    idx_sec = -1;
    for (int i = 0; i < s.size(); i++) {
        sign[i] = s[i] != s[0];
        first_oc += !sign[i];
        sec_oc += sign[i];

        if (idx_sec == -1 && sign[i])
            idx_sec = i;
    }

    t_hash.init(M1, P1, t);

    int ans = 0;

    for (int l1 = 1; l1 < t.size(); l1++) {
        ll l2 = t.size() - (ll)first_oc * l1;

        if (l2 <= 0 || l2 % sec_oc)
            continue;

        l2 /= sec_oc;

        ans += check_combo(l1, l2);
    }

    cout << ans << endl;

    return 0;
}