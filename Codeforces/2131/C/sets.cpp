#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> s, t;
map<int, int> c1, c2;

void solve(void) {
    scanf("%d %d", &N, &K);

    s.resize(N);
    t.resize(N);
    c1.clear();
    c2.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
        c1[s[i] % K]++;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
        c2[t[i] % K]++;
    }

    bool good = true;
    for (auto [v, c] : c1) {
        if (c1[v] + c1[K - v] != c2[v] + c2[K - v]) {
            good = false;
        }
    }

    if (!good) {
        printf("No\n");
    }
    else {
        printf("Yes\n");
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