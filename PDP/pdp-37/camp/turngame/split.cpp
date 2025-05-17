#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll C;

vector<int> A;

int main(void) {
    scanf("%d %lld", &N, &C);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    ll ans[2] = {0, 0};
    for (int v = 1; v <= N; v++) {
        int dir = v % 2;

        ll prv = max(ans[dir], ans[!dir] - C);
        ans[dir] = max(ans[dir], prv + v);
        ans[!dir] = max(ans[!dir], (ll)v);
    }

    ll opt = max(ans[0], ans[1]);
    printf("%lld\n", opt);

    return 0;
}