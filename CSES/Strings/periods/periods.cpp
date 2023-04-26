#include <bits/stdc++.h>

using namespace std;

struct StringHash {

    int B;
    long long MOD;

    vector<long long> p;
    vector<long long> hash;

    void init(string& s, int b, int m) {
        B = b;
        MOD = m;
        p.resize(s.size());
        p[0] = 1;
        for (int i = 1; i < p.size(); i++) {
            p[i] = p[i-1] * B % MOD;
        }
        hash.resize(s.size() + 1);
        hash[0] = 0;
        for (int i = 0; i < s.size(); i++)
            hash[i + 1] = (hash[i] * B + s[i]) % MOD;
    }

    long long getHash(int start, int end) {
        long long val = (hash[end + 1] - (hash[start] * p[end - start + 1])) % MOD;
        return (val + MOD) % MOD;
    }
};

int n;
string s;
StringHash h1;
vector<bool> isgood;

bool check_period(int len)
{
    bool cur_good = true;
    for (int nstart = 0; nstart < n && cur_good; nstart += len) {
        int add = min(len, n - nstart);
        cur_good = h1.getHash(0, add-1) == h1.getHash(nstart, nstart + add-1);
    }

    return cur_good;
}

int main(void)
{
    iostream::sync_with_stdio(false);
    cin >> s;
    n = s.size();
    h1.init(s, 29, 1e9 + 7);
    isgood.resize(n+1);

    for (int len = 1; len <= n; len++)
        if (!isgood[len] && check_period(len)) {
            isgood[len] = true;
            for (int i = 2 * len; i <= n; i += len)
                isgood[i] = true;
        }

    for (int i = 0; i <= n; i++)
        if (isgood[i])
            printf("%d ", i);

    printf("\n");
}