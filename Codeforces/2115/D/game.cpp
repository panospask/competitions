#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(var, pos) (((var) & (1LL << pos)) != 0)

using namespace std;

typedef long long ll;

int N;
vector<vector<ll>> moves;

vector<int> c;

// dp[i][f]:
// With what moves can I win the current bit?
vector<vector<int>> dp;

// Maybe some transitions are banned
vector<vector<vector<bool>>> banned;

void solve(void) {
    scanf("%d", &N);

    c.resize(N + 1);
    moves.assign(N, vector<ll>(2));
    banned.assign(N, vector<vector<bool>>(2, vector<bool>(2, false)));
    dp.assign(N + 1, vector<int>(2, false));

    for (int i = 0; i < N; i++) {
        scanf("%lld", &moves[i][0]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%lld", &moves[i][1]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%1d", &c[i]);
    }

    ll ans = 0;
    for (int b = 59; b >= 0; b--) {
        c[N] = 0;
        dp[N][0] = 1;
        dp[N][1] = 0;
        for (int i = N - 1; i >= 0; i--) {
            for (int s = 0; s < 2; s++) {

                bool winning = false;
                for (int t = 0; t < 2; t++) {
                    if (banned[i][s][t]) {
                        continue;
                    }

                    int s_new = s ^ CHECK_BIT(moves[i][t], b);
                    if (dp[i + 1][s_new] ^ (c[i] != c[i + 1])) {
                        // This is a winner state
                        winning = true;
                    }
                }

                dp[i][s] = winning;

                // Ban the states that do not result to win(if win found)
                for (int t = 0; t < 2; t++) {
                    if (banned[i][s][t]) {
                        continue;
                    }

                    int s_new = s ^ CHECK_BIT(moves[i][t], b);
                    if ((dp[i + 1][s_new] ^ (c[i] != c[i + 1])) == false && winning) {
                        banned[i][s][t] = true;
                    }
                }
            }
        }

        // Figure out who got the bit
        if (dp[0][0] ^ c[0] == false) {
            ans = ans ^ (1LL << b);
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}