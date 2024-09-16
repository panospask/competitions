#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int CUT = 450;
const int MOD = 998244353;

int N;
vector<int> A;

vector<int> dp;
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

    A.resize(N);
    dp.resize(N);
    pref.assign(N, vector<int>(CUT, 0));

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int ans = 0;
    dp[0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < CUT; j++) {
            if (i - j >= 0) {
                pref[i][j] = pref[i - j][j];
            }
            add(dp[i], pref[i][j]);
        }

        if (A[i] >= CUT) {
            for (int x = 1; i + x * A[i] < N; x++) {
                add(dp[i + x * A[i]], dp[i]);
            }
        }
        else {
            add(pref[i][A[i]], dp[i]);
        }

        add(ans, dp[i]);
    }

    printf("%d\n", ans);
}