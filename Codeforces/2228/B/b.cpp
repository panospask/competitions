#include <bits/stdc++.h>

using namespace std;

int N, K, x1, x2;

void solve(void) {
    scanf("%d %d %d %d", &N, &x1, &x2, &K);

    if (N <= 3) {
        printf("1\n");
        return;
    }

    if (x1 > x2) {
        swap(x1, x2);
    }
    int mindist = min(x2 - x1, (N - x2) + x1);
    printf("%d\n", mindist + K);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}