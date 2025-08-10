#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a, b;

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] > b[i]) {
            ans += a[i] - b[i];
        }
    }

    printf("%d\n", ans + 1);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}