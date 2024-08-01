#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

int N, T;

/* dp[i][mask]: True if we can turn of all the lights in mask withing the first i moves
 * false otherwise
 */
vector<vector<bool>> dp;

/* rep[mask]: Representative of mask
 *
 */
vector<int> rep;

int main(void)
{
    scanf("%d %d", &T, &N);

    // We will need at most 3N moves
    dp.resize(3 * N + 1, vector<bool>(1 << N));
    rep.assign(1 << N, -1);

    // For each mask, find the representative so we dont have to calculate cyclic shifts mutliple times
    for (int mask = 0; mask < 1 << N; mask++) {
        int m = mask;
        while (rep[m] == -1) {
            rep[m] = mask;
            
            // Shift m to the right once
            int bit = m & 1;
            m >>= 1;
            m += bit << (N - 1);
        }
    }

    dp[0][0] = true;
    for (int i = 0; i < 3 * N; i++) {
        // We consider the i moves made to be the moves 2, 3, .., i + 1
        // The effect move 1 will have on the mask is toggling i + 1 consecutive lights

        int toggle = (1 << ((i % N) + 1)) - 1;

        for (int mask = 0; mask < (1 << N); mask++) {
            if (dp[i][rep[mask]]) {
                dp[i + 1][rep[mask ^ toggle]] = true;
            }
        }
    }

    while (T--) {
        int lights = 0;
        for (int i = 0; i < N; i++) {
            int l;
            scanf("%1d", &l);
            if (l) {
                lights += (1 << (N - i - 1));
            }
        }

        int switches = 0;
        for (int i = 0; i < N; i++) {
            int l;
            scanf("%1d", &l);
            if (l) {
                switches += (1 << (N - i - 1));
            }
        }

        int moves = 0;

        // Effect of the switches that are originally turned on
        int effect = 0;
        while (dp[moves][rep[lights ^ effect]] == false) {
            moves++;

            effect ^= switches;

            int bit = switches & 1;
            // Shift switches to the right
            switches >>= 1;
            // Move the bit in position 0 to position N - 1
            switches += bit << (N - 1);
        }

        printf("%d\n", moves);
    }

    return 0;
}