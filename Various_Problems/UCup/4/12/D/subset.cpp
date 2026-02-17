#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;
vector<int> dp;

int main(void) {
    scanf("%d", &N);

    A.resize(1 << N);
    for (int i = 0; i < (1 << N); i++) {
        scanf("%d", &A[i]);
    }

    int S = 1;
    for (int i = 0; i < N; i++) {
        S *= 3;
    }
    dp.assign(S, 0);

    int ans = 0;
    for (int s = 0; s < S; s++) {
        int b = S / 3;
        bool found = false;
        for (int i = N - 1; i >= 0 && !found; i--) {
            int d = (s / b) % 3;

            if (d == 2) {
                dp[s] = dp[s - b] + dp[s - 2 * b];
                found = true;
            }

            b /= 3;
        }

        if (!found) {
            int q = 0;
            int b = S / 3;
            for (int i = N - 1; i >= 0; i--) {
                int d = (s / b) % 3;

                if (d == 1) {
                    q += (1 << i);
                }

                b /= 3;
            }

            dp[s] = A[q];
        }

        ans = ans ^ dp[s];
    }

    printf("%d\n", ans);
}