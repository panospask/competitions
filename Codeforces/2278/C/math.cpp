#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    int sum = 0;
    bool inside = false;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        sum += A[i];
        if (i > 0 && i < N - 1 && A[i] > 1) {
            inside = true;
        }
    }

    if (inside) {
        printf("%d\n", sum - 1);
    }
    else if (A[0] > 1 || A[N - 1] > 1) {
        printf("%d\n", sum - (N - 1));
    }
    else {
        printf("%d\n", -1);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}