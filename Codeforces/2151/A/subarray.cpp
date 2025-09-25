#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
vector<int> A;

void solve(void) {
    scanf("%d %d", &N, &M);

    A.resize(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &A[i]);
    }

    int ans = 0;
    for (int i = 1; i < M; i++) {
        if (A[i] <= A[i - 1]) {
            // Found the break point
            ans = 1;
        }
    }

    if (ans == 0) {
        ans = N - A.back() + 1;
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