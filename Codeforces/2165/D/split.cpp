#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<pi> A;

vector<set<int>> idx;

int ans = 0;

bool test(int v, int j) {
    auto it = idx[v].lower_bound(j);
    if (it != idx[v].begin()) {
        it--;
        idx[v].erase(it);
        ans--;
        return true;
    }

    return false;
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    idx.assign(2 * N + 2, set<int>());
    ans = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
        idx[A[i].first].insert(A[i].second);
    }
    sort(A.begin(), A.end());

    ans = 0;
    for (int i = 0; i < N; i++) {
        int j = A[i].second;
        int v = A[i].first;

        ans++;
        if (!test(v - 1, j)) {
            test(v + 1, j);
        }
    }

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