#include <bits/stdc++.h>

using namespace std;

const int MAXV = 5000;

int N;
vector<int> A;

int target;
vector<int> dist;

int gcd(int a, int b) {
    if (a < b) {
        swap(a, b);
    }

    while (b) {
        a = a % b;
        swap(a, b);
    }

    return a;
}

int bfs(void) {
    queue<int> q;

    for (int v = 0; v <= MAXV; v++) {
        if (dist[v] == 0) {
            q.push(v);
        }
    }

    while (true) {
        int u = q.front();
        q.pop();

        if (u == target) {
            return dist[u];
        }

        for (int i = 0; i < N; i++) {
            int g = gcd(A[i], u);
            if (dist[g] == -1) {
                dist[g] = dist[u] + 1;
                q.push(g);
            }
        }
    }
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    dist.assign(MAXV + 1, -1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    target = A[0];
    for (int i = 0; i < N; i++) {
        target = gcd(target, A[i]);
        dist[A[i]] = 0;
    }

    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] == target) {
            cnt++;
        }
    }

    int ans = 0;
    if (cnt) {
        ans = N - cnt;
    }
    else {
        ans = bfs() + N - 1;
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