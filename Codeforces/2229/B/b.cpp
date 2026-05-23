#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A,B;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    B.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    ll ans = 0;
    int maxv = 0;
    for (int i = 0; i < N; i++) {
        ans += max(A[i], B[i]);
        maxv = max(maxv, min(A[i], B[i]));
    }

    printf("%lld\n", ans + maxv);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}