#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N, M, K;
//dp[i][j][down][right]
vector<vector<vector<vector<ll>>>> dp;

bool joined(int i1, int j1, int i2, int j2) {
    ;
}

void solve(void) {
    scanf("%d %d %d", &N, &M, &K);

    dp.assign(N, vector<vector<vector<ll>>>(M, vector<vector<ll>>(2, vector<ll>(2, 0))));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int d = 0; d < 2; d++) {
                for (int r = 0; r < 2; r++) {
                    ;
                }
            }
        }
    }
}

int main(void) {
    ;
}