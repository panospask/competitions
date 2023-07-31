#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define CHECK_BIT(val, pos) (val & (1 << pos))

using namespace std;

typedef long long ll;

const int MAXN = 18;

int N;

// dp[i][j]: Different ways s.t we are at node j and are trying to create a cycle to node high(i)
ll dp[1 << MAXN][MAXN];
ll ans[1 << MAXN];
bool match[MAXN][MAXN];

int main(void)
{
    // freopen("redistribute.in", "r", stdin);
    // freopen("redistribute.out", "w", stdout);

    scanf("%d", &N);
    ans[0] = 1;
    for (int i = 0; i < N; i++) {
        bool found = false;
        for (int j = 0; j < N; j++) {
            int num;
            scanf("%d", &num);
            num--;

            match[i][num] = !found;

            found = found || num == i;
        }
    }

    // Set dp
    for (int i = 0; i < N; i++)
        for (int s = 0; s < 1 << N; s++)
            dp[s][i] = 0;

    // Calculate dp
    for (int i = 0; i < N; i++)
        dp[1 << i][i] = 1;

    for (int s = 1; s < 1 << N; s++) {
        for (int i = 0; i < N; i++) {
            if (dp[s][i] == 0)
                continue;

            int gift = 31 - __builtin_clz(s);
            int cow = i;

            for (int j = 0; j < N; j++) {
                if (CHECK_BIT(s, j))
                    continue;
                // Insert cow j into the cycle
                if (j < gift) {
                    if (match[cow][j]) {
                        // Continue cycle
                        dp[s + (1 << j)][j] += dp[s][i];
                    }
                }
                else {
                    if (match[cow][gift]) {
                        // Close cycle and start new
                        dp[s + (1 << j)][j] += dp[s][i];
                    }
                }
            }

            if (match[cow][gift])
                ans[s] += dp[s][i];
        }
    }

    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int mask1 = 0;
        int high = 0;
        int shigh = 0;
        for (int i = 0; i < N; i++) {
            char c;
            scanf(" %c", &c);

            if (c == 'H') {
                high = i;
                mask1 += (1 << i);
            }
            else {
                shigh = i;
            }
        }

        int mask2 = (1 << N) - 1 - mask1;

        printf("%lld\n", ans[mask1] * ans[mask2]);
    }

    return 0;
}