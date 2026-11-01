#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    sort(A.begin(), A.end());

    ll cost = 0;
    int operations = 0;
    for (int i = 0; i < N / 2; i++) {
        int cur = (i + 1);
        int times = A[i + 1] - A[i];
        cost += (ll)times * cur;
        operations += times;
    }
    for (int i = N - 1; i > N / 2; i--) {
        int cur = (N - i);
        int times = A[i] - A[i - 1];
        cost += (ll)times * cur;
        operations += times;
    }

    printf("%lld %lld\n", cost, operations);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}