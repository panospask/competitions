#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

const int B = 29;
vector<ll> p;

struct StringHash {

    ll M = 1e9 + 7;

    vector<ll> hash;

    void init(string& s) {
        hash.resize(s.size() + 1);
        if (p.size() < s.size() + 1)
            p.resize(s.size() + 1);

        hash[0] = 0;
        p[0] = 1;
        for (int i = 0; i < s.size(); i++) {
            p[i + 1] = p[i] * B % M;
            hash[i + 1] = (hash[i] * B + (s[i]-'a')) % M;
        }
    }

    ll getHash(int start, int end) {
        ll val = (hash[end + 1] - (hash[start] * p[end - start + 1])) % M;
        return (val + M) % M;
    }
};

int n, m;
vector<StringHash> spotty;
vector<StringHash> plain;
vector<int> existing_hashes;

bool check_positions(int start, int end)
{
    existing_hashes.resize(n);
    for (int i = 0; i < n; i++) {
        ll val = spotty[i].getHash(start, end);
        existing_hashes[i] = val;
    }
    sort(existing_hashes.begin(), existing_hashes.end());

    for (int i = 0; i < n; i++) {
        ll val = plain[i].getHash(start, end);
        if (lower_bound(existing_hashes.begin(), existing_hashes.end(), val) != upper_bound(existing_hashes.begin(), existing_hashes.end(), val))
            return false;
    }

    return true;
}

bool is_enough(int len)
{
    for (int l = 0; l <= m - len; l++) {
        int r = l + len - 1;
        if (check_positions(l, r))
            return true;
    }

    return false;
}

int main(void)
{
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin >> n >> m;
    spotty.resize(n);
    plain.resize(n);
    for (int i = 0; i < n; i++) {
        string cow;
        cin >> cow;
        spotty[i].init(cow);
    }
    for (int i = 0; i < n; i++) {
        string cow;
        cin >> cow;
        plain[i].init(cow);
    }

    int l = 0; //is_enough(l) = false
    int r = m; // is_enough(r) = true
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (is_enough(mid))
            r = mid;
        else
            l = mid;
    }

    cout << r << endl;
    return 0;
}