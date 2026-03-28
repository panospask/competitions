#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N, D;
vector<pi> A;

int main(void) {
    scanf("%d %d", &N, &D);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &A[i].first, &A[i].second);
    }

    sort(A.begin(), A.end());

    ll ans = 0;
    ll cur = 0;

    int p = 0;
    for (int i = 0; i < N; i++) {
        if (i) {
            cur -= A[i - 1].second;
        }

        while (p < N && A[i].first + D > A[p].first) {
            cur += A[p].second;
            p++;
        }
        ans = max(ans, cur);
    }

    printf("%lld\n", ans);
}