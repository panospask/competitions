#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

void solve(void) {
    scanf("%d", &N);

    a.resize(N);

    bool zero = false;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);

        zero = zero || (a[i] == 0);
    }

    bool good = true;
    for (int i = 0; i < N - 1; i++) {
        if (a[i] == 0 && a[i + 1] == 0) {
            good = false;
        }
    }

    if (zero && good) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
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