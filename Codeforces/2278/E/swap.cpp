#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;

vector<int> positions[2];

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    positions[0].clear();
    positions[1].clear();
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);

        bool s = (i % 2);
        if (A[i] > 0) {
            positions[s].push_back(A[i]);
        }
        else {
            positions[!s].push_back(-A[i]);
        }
    }
    sort(positions[0].rbegin(), positions[0].rend());
    sort(positions[1].rbegin(), positions[1].rend());

    ll ans = 0;

    int cnt[2];
    cnt[0] = (N + 1) / 2;
    cnt[1] = N / 2;
    for (int s = 0; s < 2; s++) {
        for (int i = 0; i < positions[s].size(); i++) {
            if (i < cnt[s]) {
                ans += positions[s][i];
            }
            else {
                ans -= positions[s][i];
            }
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