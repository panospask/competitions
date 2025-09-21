#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> ans;
vector<int> pos;

void solve(void) {
    scanf("%d", &N);

    ans.resize(2 * N + 1);

    for (int i = 1; i < N; i++) {
        ans[i] = ans[2 * N - i] = N - i;
    }
    ans[N] = ans[2 * N] = N;

    for (int i = 1; i <= 2*  N; i++) {
        printf("%d ", ans[i]);
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