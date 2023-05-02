#include <bits/stdc++.h>
#define CHARVAL(x) ((x) - 'a')

using namespace std;

typedef long long ll;

struct HashString {

    int M, B;
    vector<ll> p;
    vector<ll> hash;

    void init(string& s, int m, int b)
    {
        M = m;
        B = b;
        p.resize(s.size() + 1);
        hash.resize(s.size() + 1);

        p[0] = 1;
        hash[0] = 0;
        for (int i = 0 ; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * B + CHARVAL(s[i])) % M;
            p[i + 1] = p[i] * B % M;
        }
    }

    ll getHash(int l, int r)
    {
        ll rawval = hash[r + 1] - (hash[l] * p[r - l + 1]) % M;
        return (rawval + M) % M;
    }
};

string s;
HashString h;

// True if the suffixes[x-len..x] and [n-len..n] are the same
bool equalhash(int x, int len)
{
    // cout << "Check from: " << x - len + 1 << " to " << x  << ". Length: " << len << endl;
    return h.getHash(x - len + 1, x) == h.getHash(s.size() - len, s.size() - 1);
}

void answer_query(void)
{
    int x;
    cin >> x;
    x--;

    int l = 0;
    int r = x + 2;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (equalhash(x, mid))
            l = mid;
        else
            r = mid;
    }

    cout << l << '\n';
    return;
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> s;
    h.init(s, 1e9 + 7, 31);

    int q;
    cin >> q;
    while (q--) {
        answer_query();
    }

    return 0;
}