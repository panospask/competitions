#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> w;

void solve(void) {
    scanf("%d", &N);

    int cnt[3] = {0, 0, 0};

    w.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &w[i]);
        cnt[w[i] % 3]++;
    }

    int ans = 0;
    ans += cnt[0];
    ans += min(cnt[1], cnt[2]);
    ans += (max(cnt[1], cnt[2]) - min(cnt[1], cnt[2])) / 3;

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}