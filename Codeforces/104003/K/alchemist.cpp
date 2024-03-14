#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct HashString {

    int MOD = 1e9 + 7;
    int P = 31;
    vector<ll> hash;
    vector<ll> pow;

    void init(string& s) {
        hash.resize(s.size() + 1);
        pow.resize(s.size() + 1);

        hash[0] = 0;
        pow[0] = 1;

        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * P + s[i] - 'a' + 1) % MOD;
            pow[i + 1] = pow[i] * P % MOD;
        }
    }

    int getHash(int l, int r) {
        ll res = hash[r + 1] - hash[l] * pow[r - l + 1] % MOD;
        return (res % MOD + MOD) % MOD;
    }

    int full(void) {
        return hash.back();
    }
};

int n;
vector<string> words;
vector<HashString> hashes;
vector<bool> removed;
vector<int> nums;
vector<vector<int>> min_add;

int test(void)
{
    int total = words[nums.front()].size();
    int prv = nums.front();

    for (int i = 1; i < nums.size(); i++) {
        total += min_add[prv][nums[i]];
        prv = nums[i];
    }

    return total;
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n;
    words.resize(n);
    hashes.resize(n);
    removed.assign(n, false);

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        hashes[i].init(words[i]);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (removed[i] || removed[j] || i == j)
                continue;

            // Check if i removes j;
            int len = words[j].size();
            for (int k = 0; k <= (int)words[i].size() - len; k++) {
                if (hashes[i].getHash(k, k + len - 1) == hashes[j].full()) {
                    removed[j] = true;
                    break;
                }
            }
        }

    // Now save only those who did not get removed
    vector<string> tmp_str;
    vector<HashString> tmp_hash;
    for (int i = 0; i < n; i++)
        if (!removed[i]) {
            tmp_str.push_back(words[i]);
            tmp_hash.push_back(hashes[i]);
        }

    swap(words, tmp_str);
    swap(hashes, tmp_hash);
    tmp_str.clear();
    tmp_hash.clear();

    n = words.size();

    // Figure out how much would each pairing cost
    min_add.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;

            // Check how much can be saved by putting j after i i.e
            // The biggest prefix of j that is also a suffix of i
            int saved = 0;
            int l_j = 0;
            int r_i = words[i].size() - 1;
            for (int len = 1; len <= min(words[i].size(), words[j].size()); len++) {
                int l_i = words[i].size() - len;
                int r_j = len - 1;

                if (hashes[i].getHash(l_i, r_i) == hashes[j].getHash(l_j, r_j))
                    saved = len;
            }

            min_add[i][j] = words[j].size() - saved;
        }

    nums.resize(n);
    for (int i = 0; i < n; i++)
        nums[i] = i;

    int ans = test();
    while (next_permutation(nums.begin(), nums.end()))
        ans = min(ans, test());

    cout << ans << endl;

    return 0;
}