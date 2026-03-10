#include <bits/stdc++.h>

using namespace std;

const int LETTERS = 26;

int N, K;
vector<int> cnt;

void solve(void) {
    scanf("%d %d", &N, &K);

    cnt.assign(LETTERS, 0);
    for (int i = 0; i < N; i++) {
        char x;
        scanf(" %c", &x);

        cnt[x - 'a']++;
    }

    int ans = 0;
    for (int l = 1; l <= N; l++) {
        // Test if l is feasible

        int numcycles = __gcd(l, K);
        int cycle = l / numcycles;

        for (int c = 0; c < LETTERS; c++) {
            numcycles -= cnt[c] / cycle;
        }
        if (numcycles <= 0) {
            ans = l;
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
}