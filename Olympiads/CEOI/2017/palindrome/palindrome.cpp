#include <bits/stdc++.h>
#define M1 ((int)1e9 + 7)
#define M2 ((int) 100663319)

using namespace std;

typedef long long ll;

struct StringHash {

    ll M;
    int B;

    vector<ll> p;
    vector<ll> hash;

    void init(string& s, ll m, int b) {
        M = m;
        B = b;

        p.resize(s.size() + 1);
        hash.resize(s.size() + 1);
        p[0] = 1;
        hash[0] = 0;

        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * B + (s[i] - 'a')) % M;
            p[i + 1] = p[i] * B % M;
        }
    }

    ll getHash(int start, int end) {
        ll val = (hash[end + 1] - (hash[start] * p[end - start + 1])) % M;
        val = (val + M) % M;
        return val;
    }
};

StringHash h1, h2;

void solve(void)
{
    string s;
    cin >> s;

    h1.init(s, M1, 26);
    h2.init(s, M2, 30);

    int l1 = 0;
    int r2 = s.size() - 1;
    int len = 1;
    int ans = 0;
    while (l1 + len - 1 < r2 - len + 1) {
        int r1 = l1 + len - 1;
        int l2 = r2 - len + 1;

        if (h1.getHash(l1, r1) == h1.getHash(l2, r2) && h2.getHash(l1, r1) == h2.getHash(l2, r2)) {
            ans += 2;
            l1 = r1 + 1;
            r2 = l2 - 1;
            len = 0;
        }

        len++;
    }

    if (l1 <= r2)
        ans++;

    printf("%d\n", ans);
    return;
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