#include <bits/stdc++.h>

using namespace std;

void solve(void) {
    int N, M, D;
    scanf("%d %d %d", &N, &M, &D);

    int top = D / M;
    int ans = ((N + top) / (top + 1));

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}