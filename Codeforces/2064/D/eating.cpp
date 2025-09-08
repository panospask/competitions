#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)

using namespace std;

const int BITS = 30;

int N, Q;
vector<int> w;
vector<vector<int>> suff;
// prv[b][i]: Position LESS than i and has 1 in bit b
vector<vector<int>> prv;

void solve(void) {
    scanf("%d %d", &N, &Q);

    w.resize(N);
    suff.assign(BITS, vector<int>(N + 1, 0));
    prv.assign(BITS, vector<int>(N + 1));
    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
    }

    for (int b = 0; b < BITS; b++) {
        for (int i = N - 1; i >= 0; i--) {
            suff[b][i] = CHECK_BIT(w[i], b);
            suff[b][i] ^= suff[b][i + 1];
        }

        prv[b][0] = -1;
        for (int i = 1; i <= N; i++) {
            if (CHECK_BIT(w[i - 1], b)) {
                prv[b][i] = i - 1;
            }
            else {
                prv[b][i] = prv[b][i - 1];
            }
        }
    }

    while (Q--) {
        int x;
        scanf("%d", &x);

        int pos = N - 1;
        int bit = BITS - 1;
        // Next certain failure
        int fail = -1;
        int ans = 0;
        while (pos > fail && bit >= 0) {
            int target = CHECK_BIT(w[pos], bit);
            int cur = suff[bit][pos + 1] ^ CHECK_BIT(x, bit);

            if (cur > target) {
                // We win --> Go to next position
                pos = prv[bit][pos];
            }
            else if (cur < target) {
                fail = pos;
            }
            else {
                // This bit is 0 certainly (after this pos)
                // Just move to next bit and update fail
                fail = max(fail, prv[bit][pos]);
                bit--;
            }
        }

        printf("%d ", N - 1 - max(fail, pos - 1));
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        solve();
    }

    return 0;
}