#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9;

int N;
vector<pi> columns;

void solve(void) {
    scanf("%d", &N);

    columns.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &columns[i].first);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &columns[i].second);
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += max(columns[i].first, columns[i].second);
    }

    int opt = -INF;
    for (int i = 0; i < N; i++) {
        opt = max(opt, min(columns[i].first, columns[i].second));
    }

    printf("%d\n", opt + ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}