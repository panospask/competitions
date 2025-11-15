#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

int N, X;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    int mn = INF;
    int mx = -INF;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        mn = min(A[i], mn);
        mx = max(A[i], mx);
    }
    scanf("%d", &X);

    if (mn > X || mx < X) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}