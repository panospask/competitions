#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

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

    ll ways = 1;
    int used = 0;
    int ex = 1;
    for (int i = N - 2; i >= 0; i--) {
        if (A[i] >= 2 * N + 10) {
            printf("0\n");
            return;
        }
        exclude[A[i]] = true;
        if (A[i] == A[i + 1]) {
            // B[i + 1] is something smaller
            while (exclude[p]) {
                p++;
            }
            if (p > A[i]) {
                printf("0\n");
                return;
            }

            ways = ways * (A[i] - used - ex + 1) % MOD;

            B[i + 1] = p;
            p++;
            used++;
        }
        else if (A[i] > A[i + 1]) {
            B[i + 1] = 1e9;
            ways = ways * (N - ex + 1) % MOD;
            ex++;

        }
        else {
            printf("0\n");
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
        printf("0\n");
        return;
    }

    while (exclude[p]) {
        p++;
    }


    printf("%lld\n", ways);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}