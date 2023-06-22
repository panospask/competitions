#include <bits/stdc++.h>
#define s second
#define f first

using namespace std;

typedef long long ll;
typedef __int128_t lll;

const ll MOD = (1ll << 61) - 1;
ll desired_pow = 1;
const int P = 31;

struct StringHash {

    vector<ll> hash;

    void init(string& st) {
        hash.resize(st.size() + 1);

        hash[0] = 0;
        for (int i = 0; i < st.size(); i++) {
            hash[i + 1] = ((lll)hash[i] * P + st[i] - 'a' + 1) % MOD;
        }
    }

    ll get(int l, int len) {
        int r = l + len - 1;
        lll res = hash[r + 1] - (lll)hash[l] * desired_pow % MOD;

        return ((res % MOD) + MOD) % MOD;
    }
};

const int DIRS = 4;
const int d_i[4] = {1, 0, 1, 1};
const int d_j[4] = {0, 1, 1, -1};

int n, m, k;
vector<string> words;
int len;
vector<vector<bool>> visited;

unordered_map<ll, int> all;

void generate_string(int or_i, int or_j, int d_i, int d_j)
{
    string beg;

    int cur = 0;
    int i = or_i;
    int j = or_j;
    // Create the string
    while ((i != or_i) || (j != or_j) || !cur) {
        beg.push_back(words[i][j]);
        cur++;

        i += d_i;
        j += d_j;

        i = (i + m) % m;
        j = (j + n) % n;
    }

    string b2 = beg;
    reverse(b2.begin(), b2.end());

    int l = beg.length();

    string st = beg;
    string st2 = b2;
    while (st.size() < cur + len - 1) {
        int ap = min(l, cur + len - 1 - l);

        st += beg.substr(0, ap);
        st2 += b2.substr(0, ap);
    }

    // Hash the string and calculate it
    StringHash cur_hash;
    cur_hash.init(st);
    StringHash cur_hash2;
    cur_hash2.init(st2);

    i = or_i;
    j = or_j;
    cur = 0;
    while (!visited[i][j]) {
        all[cur_hash.get(cur, len)]++;
        all[cur_hash2.get(cur, len)]++;
        visited[i][j] = true;
        cur++;

        i = i + d_i;
        j = j + d_j;

        i = (i + m) % m;
        j = (j + n) % n;
    }
}

ll gcd(ll a, ll b)
{
    while (b != 0) {
        swap(b, a %= b);
    }

    return a;
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

int main(void)
{
    cin >> m >> n >> k;

    len = min(lcm(n, m), k);

    for (int i = 0; i < len; i++)
        desired_pow = (lll)desired_pow * P % MOD;

    words.resize(m);

    for (int i = 0; i < m; i++) {
        words[i].resize(n);
        for (int j = 0; j < n; j++)
            scanf(" %c", &words[i][j]);
    }

    for (int x = 0; x < DIRS; x++) {
        visited.assign(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j])
                    generate_string(i, j, d_i[x], d_j[x]);
            }
        }
    }

    ll total_combo = (8 * n * m) * (ll)(8 * n * m);
    ll total_same = 0;

    for (auto& v : all) {
        total_same += (ll)v.s * v.s;
    }

    // sort(all.begin(), all.end());

    // ll cur_num = -1;
    // int cur_same = 0;
    // for (int i = 0; i < all.size(); i++) {
    //     if (all[i] == cur_num)
    //         cur_same++;
    //     else {
    //         total_same += (ll)cur_same * cur_same;
    //         cur_num = all[i];
    //         cur_same = 1;
    //     }
    // }
    // total_same += (ll)cur_same * cur_same;

    ll d = gcd(total_combo, total_same);

    total_combo /= d;
    total_same /= d;

    printf("%lld/%lld\n", total_same, total_combo);

    return 0;
}