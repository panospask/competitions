#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;
vector<int> cnt;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    cnt.assign(N, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;
        cnt[A[i]]++;
    }

    // Total by cnt
    vector<int> total(N + 1);
    for (int i = 0; i < N; i++) {
        total[cnt[i]]++;
    }

    int ans = 0;
    for (int i = N; i > 0; i--) {
        ans = max(ans, i * total[i]);
        total[i - 1] += total[i];
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