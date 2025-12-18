#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> cnt;

void solve(void) {
    scanf("%d", &N);

    cnt.assign(N + 1, 0);
    for (int i = 0; i < N; i++) {
        int v;
        scanf("%d", &v);
        cnt[v]++;
    }

    int ans = 0;
    for (int v = 0; v <= N; v++) {
        if (cnt[v] == 0) {
            continue;
        }

        if (cnt[v] > v) {
            ans += cnt[v] - v;
        }
        else if (cnt[v] < v) {
            ans += cnt[v];
        }
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