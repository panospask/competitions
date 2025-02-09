#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

// Very big number
const int INF = 1e9;

int S, X, Y;

int main(void)
{
    freopen("shroompath.in", "r", stdin);
    freopen("shroompath.out", "w", stdout);

    int type;
    scanf("%d", &type);
    scanf("%d %d %d", &S, &X, &Y);

    // The total steps on the path so far
    ll total_steps = 0;

    // The number of sequences of length i
    ll sequences[S + 1];
    sequences[0] = 1;

    // How many A (respectively B) mushrooms we have to gather
    ll target_A = INF, target_B = INF;
    if (X > 0) {
        target_A = ((S - 1) / X) + 1;
    }
    if (Y > 0) {
        target_B = ((S - 1) / Y) + 1;
    }

    ll ans = -1;
    for (int i = 1; i <= S && ans == -1; i++) {
        sequences[i] = sequences[i - 1] * 2 % MOD;

        // The longest sequence of mushrooms type A is found in the beggining (length: 2i + 1)
        if (2 * i - 1 >= target_A) {
            ans = total_steps + target_A;
        }

        // The longest sequence of mushrooms type B is found in the middle (length: i)
        else if (i >= target_B) {
            ans = total_steps + i * sequences[i - 1] + 1;
        }

        total_steps = (total_steps + i * sequences[i]) % MOD;
    }

    ans %= MOD;
    printf("%lld\n", ans);

    return 0;
}