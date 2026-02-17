#include <bits/stdc++.h>

using namespace std;

int A, B, L;

void solve(void) {
    scanf("%d %d %d", &L, &A, &B);

    int ans = 0;
    int cur = A;
    for (int i = 0; i < L; i++) {
        ans = max(ans, cur);
        cur = (cur + B) % L;
    }

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
    solve();
    }

    return 0;
}