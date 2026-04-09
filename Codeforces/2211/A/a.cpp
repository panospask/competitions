#include <bits/stdc++.h>

using namespace std;

int N;

void solve(void) {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
    }

    if (N == 1) {
        printf("1\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        printf("2 ");
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}