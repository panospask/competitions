#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

bool check(int a, int b)
{
    int mn = min(a, b);
    int mx = max(a, b);

    if (2 * mn <= mx) {
        return false;
    }
    else {
        return true;
    }
}

void solve(void)
{
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    bool good = false;
    for (int i = 1; i < N; i++) {
        if (check(A[i - 1], A[i])) {
            good = true;
        }
    }

    if (good) {
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