#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    sort(A.begin(), A.end());

    int ans = A.back() - A[0];
    ans = (ans + 1) / 2;

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}