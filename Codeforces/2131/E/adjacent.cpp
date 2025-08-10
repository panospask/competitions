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

    bool good = (a[N - 1] == b[N - 1]);
    for (int i = N - 1; i >= 0; i--){
        if (a[i] == b[i]) {
            continue;
        }
        if ((a[i] ^ a[i + 1]) == b[i]) {
            continue;
        }
        if ((a[i] ^ b[i + 1]) == b[i]) {
            continue;
        }

        good = false;
    }

    if (good) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
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