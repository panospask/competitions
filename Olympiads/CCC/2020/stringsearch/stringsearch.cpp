#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct StringHash {

    int M, B;
    vector<ll> p;
    vector<ll> hash;

    void init(int m, int b, string& st) {
        M = m;
        B = b;

        hash.resize(st.size() + 1);
        p.resize(st.size() + 1);

        hash[0] = 0;
        p[0] = 1;
        for (int i = 0; i < st.size(); i++) {
            hash[i + 1] = (hash[i] * B + (st[i] - 'a' + 1)) % M;
            p[i + 1] = (p[i] * B) % M;
        }
    }

    int gethash(int l, int r) {
        ll res = hash[r + 1] - hash[l] * p[r - l + 1] % M;

        return (res + M) % M;
    }
};

StringHash h1, h2;

bool hashcomp(const pi& a, const pi& b)
{
    if (h1.gethash(a.f, a.s) == h1.gethash(b.f, b.s))
        return h2.gethash(a.f, a.s) < h2.gethash(b.f, b.s);
    return h1.gethash(a.f, a.s) < h1.gethash(b.f, b.s);
}

int len;
set<pi, decltype(hashcomp)*> found(hashcomp);
vector<int> freq_n, freq_t;
string n, t;

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n >> t;

    h1.init((int)1e9 + 7, 31, t);
    h2.init((int)1e9 + 7, 53, t);

    freq_t.resize(26);
    freq_n.resize(26);

    len = n.size();
    for (int i = 0; i < len; i++) {
        freq_n[n[i] - 'a']++;
        freq_t[t[i] - 'a']++;
    }
    for (int i = len; i < t.size() + 1; i++) {
        // Check for match
        bool good = true;
        for (int i = 0; i < 26; i++) {
            good = good && freq_n[i] == freq_t[i];
        }

        if (good)
            found.insert(mp(i - len, i - 1));

        if (i != t.size()) {
            freq_t[t[i - len] - 'a']--;
            freq_t[t[i] - 'a']++;
        }
    }

    cout << found.size() << endl;

    return 0;
}