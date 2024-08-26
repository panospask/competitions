#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

typedef long long ll;

int CUT = 333;

int N;
vector<int> d, x;
vector<int> dp;

vector<vector<int>> pref;

void add(int& a, int b)
{
    a += b;
    if (a > MOD) {
        a -= MOD;
    }
    if (a < 0) {
        a += MOD;
    }
}

int main(void)
{
    scanf("%d", &N);

    d.resize(N);
    x.resize(N);
    dp.assign(N, 0);
    pref.assign(N, vector<int>(CUT, 0));

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &d[i], &x[i]);
    }

    dp[0] = 1;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int v = 1; v < CUT && i - v >= 0; v++) {
            add(pref[i][v], pref[i - v][v]);
            add(dp[i], pref[i][v]);
        }

        add(ans, dp[i]);

        if (d[i] == 0) {
            continue;
        }

        if (d[i] < CUT && x[i] > CUT) {
            add(pref[i][d[i]], dp[i]);

            ll finish = i + (ll)d[i] * (x[i] + 1);
            if (finish < N) {
                add(pref[finish][d[i]], -dp[i]);
            }

            continue;
        }

        int j = i;
        while (j + d[i] < N && x[i]) {
            j = j + d[i];
            x[i]--;

            add(dp[j], dp[i]);
        }
    }

    printf("%d\n", ans);

    return 0;
}