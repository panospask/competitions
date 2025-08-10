#include <bits/stdc++.h>

using namespace std;

int N;

void solve(void) {
    scanf("%d", &N);

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        if (i % 2) {
            A[i] = 3;
        }
        else {
            A[i] = -1;
        }
    }

    if (N % 2 == 0) {
        A[N - 1] = 2;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}