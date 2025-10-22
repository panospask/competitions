#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<int> A;
vector<bool> visited;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    visited.assign(N, false);
    int ans = 0;

    priority_queue<pi, vector<pi>, greater<pi>> q;

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        q.push({A[i], i});
    }

    while (!q.empty()) {
        int u, x;
        tie(u, x) = q.top();
        q.pop();

        if (visited[x]) {
            continue;
        }
        visited[x] = true;
        ans = max(ans, u);

        if (x) {
            q.push({abs(A[x] - A[x - 1]), x - 1});
        }
        if (x + 1 < N) {
            q.push({abs(A[x + 1] - A[x]), x + 1});
        }
    }
    
    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }
}