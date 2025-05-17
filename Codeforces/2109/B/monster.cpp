#include <bits/stdc++.h>

using namespace std;

int N, M;
int a, b;

int calc(int N, int M) {
    int ans = 0;
    while (max(N, M) > 1) {
        ans++;

        int a = N / 2;
        int b = M / 2;

        // Decide where to cut  
        int c1 = max(a, N - 1 - a);
        int d1 = max(b, M - 1 - b);
        
        if ((long long)c1 * M > (long long)d1 * N) {
            N = N - c1;
        }
        else {
            M = M - d1;
        }

        a = N / 2;
        b = M / 2;
    }

    return ans;
}

void solve(void) {
    scanf("%d %d", &N, &M);
    scanf("%d %d", &a, &b);
    a--; b--;

    int c1 = max(a, N - 1 - a);
    int d1 = max(b, M - 1 - b);
    int ans = min(calc(N - c1, M), calc(N, M - d1)) + 1;

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}