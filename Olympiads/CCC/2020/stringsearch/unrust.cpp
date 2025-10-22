#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

const int LETTERS = 26;
const int M1 = 1e9 + 7;
const int M2 = 998244353;

typedef long long ll;
typedef pair<int, int> pi;

struct HashedString {
    int M;
    const int B = 31;

    vector<ll> p;
    vector<ll> hash;

    void init(int m, string& st) {
        M = m;

        p.resize(st.size() + 1);
        hash.resize(st.size() + 1);

        p[0] = 1;
        hash[0] = 0;
        for (int i = 0; i < st.size(); i++) {
            p[i + 1] = p[i] * B % M;
            hash[i + 1] = (hash[i] * B + (st[i] - 'a' + 1)) % M;
        }
    }

    // Get hash in [l, r)
    int get(int l, int r) {
        ll res = hash[r] - hash[l] * p[r - l];

        return (res % M + M) % M;
    }
};

HashedString h1, h2;

string N, H;
vector<int> freq;
vector<int> target;

set<pi> good;

bool match(void) {
    for (int l = 0; l < LETTERS; l++) {
        if (freq[l] != target[l]) {
            return false;
        }
    }

    return true;
}

int main(void) {
    ios::sync_with_stdio(false);

    cin >> N >> H;
    if (N.size() > H.size()) {
        cout << 0 << endl;
        return 0;
    }

    h1.init(M1, H);
    h2.init(M2, H);

    target.assign(LETTERS, 0);
    freq.assign(LETTERS, 0);

    for (int i = 0; i < N.size(); i++) {
        target[N[i] - 'a']++;
        freq[H[i] - 'a']++;
    }

    for (int i = N.size(); i < H.size(); i++) {
        if (match()) {
            good.insert(mp(h1.get(i - N.size(), i), h2.get(i - N.size(), i)));
        }

        freq[H[i - N.size()] - 'a']--;
        freq[H[i] - 'a']++;
    }
    if (match()) {
        good.insert(mp(h1.get(H.size() - N.size(), H.size()), h2.get(H.size() - N.size(), H.size())));
    }

    cout << good.size() << endl;
    
    return 0;
}