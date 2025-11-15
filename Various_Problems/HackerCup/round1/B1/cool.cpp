#include <bits/stdc++.h>

using namespace std;

int N, A, B;

void solve(void) {
    scanf("%d %d %d", &N, &A, &B);

    for (int i = 0; i < 2 * N - 1; i++) {
        printf("%d ", 1);
    }
    printf("%d\n", B);
}

int main(void) {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }
}