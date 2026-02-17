#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int BITS = 30;

int N, K;

void solve(void) {
    scanf("%d %d", &N, &K);

    if (K % 2 == 1) {
        for (int i = 0; i < K; i++) {
            printf("%d ", N);
        }
    }
    else {
        for (int i = 0; i < K - 2; i++) {
            printf("%d ", N);
        }

        int cnt = 0;
        int a1 = 0;
        int a2 = 0;
        for (int b = BITS - 1; b >= 0; b--) {
            if (CHECK_BIT(N, b)) {
                cnt++;
                if (cnt == 1) {
                    a1 += (1 << b);
                }
                else {
                    a2 += (1 << b);
                }
            }
            else {
                if (cnt >= 2) {
                    a1 += (1 << b);
                    a2 += (1 << b);
                }
            }
        }

        printf("%d %d", a1, a2);
    }

    printf("\n");

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}