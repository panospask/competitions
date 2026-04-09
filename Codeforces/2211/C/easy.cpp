#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> A, B, idx;

void solve(void) {
    scanf("%d %d", &N, &K);

    A.resize(N);
    B.resize(N);
    idx.assign(N + 10, -1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    bool ext = false;
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
        if (B[i] != -1) {
            if (idx[B[i]] != -1) {
                ext = true;
            }

            idx[B[i]] = i;
        }
    }
    if (ext) {
        printf("NO\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        if (idx[A[i]] == -1 || idx[A[i]] == i) {
            continue;
        }

        int j1 = i;
        int j2 = idx[A[i]];

        // We want i to never appear without j and vice versa => Both in all subarrays
        if (j1 + K < N || j2 + K < N || j1 - K >= 0 || j2 - K >= 0) {
            printf("NO\n");
            return;
        }
    }

    printf("YES\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}