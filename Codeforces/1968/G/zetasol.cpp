#include <bits/stdc++.h>

using namespace std;

struct dsu {
    int size;
    vector<int> rep;

    void init(int N) {
        size = N;
        rep.assign(N, 0);

        for (int i = 0; i < N; i++) {
            rep[i] = i;
        }
    }

    int find(int a) {
        if (rep[a] == a) {
            return a;
        }
        rep[a] = find(rep[a]);
        return rep[a];
    }

    // a becomes child of b
    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        rep[a] = b;
    }
};

int N, a, b;
string s;
dsu active;
vector<int> z;
vector<int> ans;

void calculate_zeta(void)
{
    z.resize(N);
    int l = -1, r = 0;

    z[0] = N;
    for (int i = 1; i < N; i++) {
        z[i] = 0;
        if (i < r) {
            z[i] = min(z[i - l], r - i);
        }
        while (i + z[i] < N && s[i + z[i]] == s[z[i]]) {
            z[i]++;
        }

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
}

void solve(void)
{
    cin >> N >> a >> b;
    cin >> s;

    calculate_zeta();
    active.init(N + 1);
    ans.assign(N + 1, 0);

    for (int len = 1; len <= N; len++) {
        // Calculate the maximum k such that fk = len

        int k = 0;
        int cur = 0;
        while (cur < N) {
            if (z[cur] >= len) {
                k++;
                cur = active.find(cur + len);
            }
            else {
                active.unite(cur, cur + 1);
                cur = active.find(cur + 1);
            }
        }

        ans[k] = len;
    }
    for (int i = N - 1; i >= 0; i--) {
        ans[i] = max(ans[i], ans[i + 1]);
    }

    for (int i = a; i <= b; i++) {
        cout << ans[i] << ' ';
    }
    cout << "\n";
}

int main(void)
{
    ios::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}