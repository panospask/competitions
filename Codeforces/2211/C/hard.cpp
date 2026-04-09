#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> A, B;

void solve(void) {
    scanf("%d %d", &N, &K);

    A.resize(N);
    B.resize(N);

    vector<int> cntA(N + 1, 0);
    vector<int> cntB(N + 1, 0);
    vector<int> cntFree(N + 1, 0);
    vector<int> connect(N, 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    // Leaves and joins must be respected
    for (int i = K; i < N; i++) {
        int l = i - K;

        if (A[i] == A[l]) {
            // Special case: Nothing leaves and nothing enters

            // Connect i and l
            // connect[i] = connect[l] + 1;

            if (B[i] != -1 && B[l] != -1) {
                if (B[i] != B[l]) {
                    printf("NO\n");
                    return;
                }
            }
            else if (B[i] == -1 && B[l] != -1) {
                B[i] = B[l];
            }
            else if (B[l] == -1 && B[i] != -1) {
                B[l] = B[i];
            }
            continue;
        }

        // Joining part
        if (B[i] != A[i]) {
            if (B[i] == -1) {
                B[i] = A[i];
            }
            else {
                printf("NO\n");
                return;
            }
        }
        
        // Leaving part
        if (B[l] != A[l]) {
            if (B[l] == -1) {
                B[l] = A[l];
            }
            else {
                printf("NO\n");
                return;
            }
        }
    }

    // Leaves and joins must be respected
    for (int i = N - 1; i >= K; i--) {
        int l = i - K;

        if (A[i] == A[l]) {
            // Special case: Nothing leaves and nothing enters

            // Connect i and l
            // connect[i] = connect[l] + 1;

            if (B[i] != -1 && B[l] != -1) {
                if (B[i] != B[l]) {
                    printf("NO\n");
                    return;
                }
            }
            else if (B[i] == -1 && B[l] != -1) {
                B[i] = B[l];
            }
            else if (B[l] == -1 && B[i] != -1) {
                B[l] = B[i];
            }
            continue;
        }

        // Joining part
        if (B[i] != A[i]) {
            if (B[i] == -1) {
                B[i] = A[i];
            }
            else {
                printf("NO\n");
                return;
            }
        }
        
        // Leaving part
        if (B[l] != A[l]) {
            if (B[l] == -1) {
                B[l] = A[l];
            }
            else {
                printf("NO\n");
                return;
            }
        }
    }

        // Make the first subarray equal
    for (int i = 0; i < K; i++) {
        cntA[A[i]]++;
        if (B[i] != -1) {
            cntB[B[i]]++;
        }
    }

    for (int x = 1; x <= N; x++) {
        if (cntB[x] > cntA[x]) {
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