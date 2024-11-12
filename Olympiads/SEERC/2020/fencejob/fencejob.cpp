#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int N;
vector<int> h;

// prv[i]: Maximum j s.t h[j] < h[i], or -1 if such j does not exist
vector<int> prv, nxt;
vector<vector<int>> dp;
vector<vector<int>> pref;

void add(int& a, int b)
{
    a += b;
    if (a > MOD) {
        a -= MOD;
    }
}

int main(void)
{
    scanf("%d", &N);

    h.resize(N);
    prv.resize(N);
    nxt.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &h[i]);
        h[i]--;
    }

    stack<int> s;
    for (int i = 0; i < N; i++) {
        while (!s.empty() && h[s.top()] > h[i]) {
            s.pop();
        }

        if (s.empty()) {
            prv[i] = -1;
        }
        else {
            prv[i] = s.top();
        }

        s.push(i);
    }

    stack<int> t;
    for (int i = N - 1; i >= 0; i--) {
        while (!t.empty() && h[t.top()] > h[i]) {
            t.pop();
        }

        if (t.empty()) {
            nxt[i] = N;
        }
        else {
            nxt[i] = t.top();
        }

        t.push(i);
    }

    dp.assign(N, vector<int>(N, 0));
    pref.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) {
        if (prv[i] == -1) {
            dp[0][i] = 1;
        }
    }

    for (int i = 1; i < N; i++) {
        pref[i - 1][0] = dp[i - 1][0];
        for (int j = 1; j < N; j++) {
            add(pref[i - 1][j], pref[i - 1][j - 1]);
            add(pref[i - 1][j], dp[i - 1][j]);
        }
        
        for (int j = 0; j < N; j++) {
            if (prv[j] >= i || nxt[j] <= i) {
                continue;
            }

            add(dp[i][j], pref[i - 1][j]);
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        add(ans, dp[N - 1][i]);
    }

    printf("%d\n", ans);
}