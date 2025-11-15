#include <bits/stdc++.h>

using namespace std;

int N, M;

void solve(void) {
    scanf("%d %d", &N, &M);

    if (N < M) {
        printf("NO\n");
    }
    else if (N <= 2 * M - 2) {
        printf("YES\n");
    }
    else if (N % 2 == 0) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }

    return 0;
}