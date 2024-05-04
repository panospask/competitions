#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long long lll;

struct StringHash {
    ll MOD = 1e9 + 9;
    ll M1 = 51;

    int size;
    vector<lll> pref;
    vector<lll> pow;

    void init(string& s) {
        size = s.size();
        pref.resize(size + 1);
        pow.resize(size + 1);

        pref[0] = 0;
        pow[0] = 1;
        for (int i = 0; i < size; i++) {
            pref[i + 1] = (pref[i] * M1 + (s[i] - 'a')) % MOD;
            pow[i + 1] = pow[i] * M1 % MOD;
        }
    }

    // hash from [l, r)
    ll gethash(int l, int r) {
        lll res = pref[r] - pref[l] * pow[r - l];
        return ((res % MOD) + MOD) % MOD;
    }
};

int N, a, b;
string s;
StringHash h;
vector<int> ans;

// Total number of splits we can achieve with common prefix of size x
int tot(int x)
{
    ll target = h.gethash(0, x);

    int cnt = 0;
    for (int l = 0; l <= N - x; l++) {
        if (h.gethash(l, l + x) == target) {
            cnt++;
            l = l + x - 1;
        }
    }

    return cnt;
}

void solve(void)
{
    scanf("%d %d %d", &N, &a, &b);

    cin >> s;
    h.init(s);

    ans.assign(N + 1, 0);

    // Calculate the first sqrt(N) numbers independently
    int cut;
    if (N <= 10) {
        cut = N;
    }
    else {
        cut = sqrt(N / log2(N));
    }

    for (int len = 1; len <= cut; len++) {
        int l = 0;
        int r = N/len + 1;
        while (l + 1 < r) {
            int mid = (l + r) / 2;
            if (tot(mid) >= len) {
                l = mid;
            }
            else {
                r = mid;
            }
        }

        ans[len] = l;
    }

    // Check the smallest sqrt(N) values of x
    for (int x = N / cut; x >= 1; x--) {
        int maxv = tot(x);

        ans[maxv] = max(ans[maxv], x);
    }
    for (int i = N - 1; i >= 0; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }

    for (int i = a; i <= b; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}