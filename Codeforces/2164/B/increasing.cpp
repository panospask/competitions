#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (((A[i] % A[j]) % 2) == 0) {
                printf("%d %d\n", A[j], A[i]);
                return;
            }
        }
    }

    printf("-1\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}