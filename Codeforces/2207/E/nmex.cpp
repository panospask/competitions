#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;
vector<int> B;
vector<bool> exclude;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    B.resize(N);
    exclude.assign(2 * N + 10, false);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    exclude[A[N - 1]] = true;
    int prv = A[N - 1];
    int p = 0;
    for (int i = N - 2; i >= 0; i--) {
        if (A[i] >= 2 * N + 10) {
            printf("NO\n");
            return;
        }
        exclude[A[i]] = true;
        if (A[i] == A[i + 1]) {
            // B[i + 1] is something smaller
            while (exclude[p]) {
                p++;
            }
            if (p > A[i]) {
                printf("NO\n");
                return;
            }
            B[i + 1] = p;
            p++;
        }
        else if (A[i] > A[i + 1]) {
            B[i + 1] = 1e9;
        }
        else {
            printf("NO\n");
            return;
        }
    }

    if (A[0] == N) {
        while (exclude[p])
            p++;
        B[0] = p;
    }
    else if (N > A[0]) {
        B[0] = 1e9;
    }
    else {
        printf("NO\n");
        return;
    }

    while (exclude[p]) {
        p++;
    }


    printf("YES\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", B[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}