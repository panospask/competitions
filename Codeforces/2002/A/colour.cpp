#include <bits/stdc++.h>

using namespace std;

int N, M, K;

void solve(void)
{
    scanf("%d %d %d", &N, &M, &K);

    N = min(N, K);
    M = min(M, K);

    printf("%d\n", N * M);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}