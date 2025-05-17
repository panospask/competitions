#include <bits/stdc++.h>

using namespace std;

int N;
map<int, int> cols;
map<int, int> diags;

void solve(void) {
    scanf("%d", &N);

    cols.clear();
    diags.clear();

    for (int i = 0 ; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        cols[x]++;
        diags[x + y]++;
    }

    int x, y;
    for (auto [c, p] : cols) {
        if (p % 2) {
            x = c;
            break;
        }
    }
    for (auto [d, p] : diags) {
        if (p % 2) {
            y = d - x;
            break;
        }
    }

    printf("%d %d\n", x, y);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}