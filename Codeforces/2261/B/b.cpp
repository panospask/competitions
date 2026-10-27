#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int ans = 0;
    bool found = false;
    for (int b = 29; b >= 0; b--) {
        bool good = true;
        bool once = false;
        for (int i = 0; i < N; i++) {
            if (!CHECK_BIT(A[i], b)) {
                good = false;
            }
            else {
                once = true;
            }
        }

        if (once) {
            found = true;
            ans += (1 << b);
        }
        if (!good) {
            if (once) {
                ans += (1 << b) - 1;
                break;
            }
        }
    }

    printf("%d\n", ans);

}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}