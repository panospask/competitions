#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, H;
vector<int> A;
vector<vector<ll>> total;

void calculate(int i, int m) {
    int top = A[i];
    total[i][i] = H - A[i];

    for (int j = i + m; j >= 0 && j < N; j += m) {
        top = max(top, A[j]);
        total[i][j] = total[i][j - m] + H - top;
    }
}

void solve(void) {
    scanf("%d %d", &N, &H);

    A.resize(N);
    total.assign(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        calculate(i, +1);
        calculate(i, -1);
    }

    for (int i1 = 0; i1 < N; i1++) {
        int idx = i1;
        for (int i2 = i1; i2 < N; i2++) {
            if (A[i2] > A[idx]) {
                idx = i2;
            }

            ll res = total[i1].front() + total[i2].back() + total[i1][idx] + total[i2][idx] - (H - A[idx]) - (H - A[i1]) - (H - A[i2]);
            ans = max(ans, res);
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}