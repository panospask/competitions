#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> p;

void solve(void) {
    scanf("%d", &N);

    p.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);

        if (p[i] == N) {
            swap(p[i], p[0]);
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}