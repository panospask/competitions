#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> a;

void solve(void) {
    scanf("%d %d", &N, &K);

    a.resize(N);
    int winner = 1;
    int mx = 0;
    int mn = INT_MAX;
    int times_mx = 1;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        winner = winner ^ (a[i] % 2);

        if (mx < a[i]) {
            mx = a[i];
            times_mx = 0;
        }
        if (mx == a[i]) {
            times_mx++;
        }
        mn = min(mn, a[i]);
    }

    if (mx - 1 - mn > K) {
        printf("Jerry\n");
        return;
    }
    if (mx - mn > K && times_mx > 1) {
        printf("Jerry\n");
        return;
    }
    if (winner) {
        printf("Jerry\n");
    }
    else {
        printf("Tom\n");
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