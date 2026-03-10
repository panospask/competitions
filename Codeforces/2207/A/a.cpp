#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N + 2);
    A[N] = 0;
    A[N + 1] = 0;
    int ans1 = 0, ans2 = 0;
    int ones = 0, zeros = 0;
    for (int i = 0; i <= N + 1; i++) {
        if (i < N)
            scanf("%1d", &A[i]);

        if (A[i]) {
            if (ones) {
                ones += zeros;
            }
            ones++;
            zeros = 0;
        }
        else {
            zeros++;

            if (zeros >= 2) {
                ans2 += ones;
                if (ones <= 2) {
                    ans1 += ones;
                }
                else {
                    ans1 += 2;
                    ones -= 2;
                    ans1 += ones / 2;
                }
                ones = 0;
            }
        }
    }



    printf("%d %d\n", ans1, ans2);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}