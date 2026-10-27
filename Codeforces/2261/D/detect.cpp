#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N, M;

void solve(void) {
    scanf("%d %d", &N, &M);

    int i = 1;
    int cur = 2;
    vector<pi> ans;
    while (i < N) {
        if (cur == 2) {
            cur = 0;
            ans.push_back({max(i - 1, 1), i});
        }
        ans.back().second = i;
        cur++;
        i++;
    }
    if (N != 1 && N % 2 == 1) {
        // We cannot let without cover
        ans.push_back({N - 1, N});
    }

    printf("%d\n", (int)ans.size());
    for (auto [a, b] : ans) {
        printf("%d %d\n", a, b);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}