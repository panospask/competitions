#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

void solve(void)
{
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    bool valid = true;
    for (int i = 0; i < N; i++) {
        valid = valid && A[i] > 2 * i && A[i] > 2 * (N - 1 - i);
    }

    if (valid) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}