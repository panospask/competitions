#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> kids;
vector<int> subtree;
vector<int> depth;

int root = 0;
int d = 0;
int total = 0;

int ans = 0;

bool query(int u, int k) {
    printf("? %d %d\n", u + 1, k);
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}

void answer(int node) {
    if (depth[node] == d) {
        ans = node;
        return;
    }

    for (auto kid : kids[node]) {
        if (subtree[kid]) {
            answer(kid);
        }
    }
}

void dfs(int node) {
    subtree[node] = (d == depth[node]);

    for (auto kid : kids[node]) {
        depth[kid] = depth[node] + 1;
        dfs(kid);
        subtree[node] += subtree[kid];
    }
}

void calculate(int node) {
    if (subtree[node] <= total / 2) {
        // This is it
        int ans = query(node, d - depth[node]);

        if (ans) {
            total = subtree[node];
            root = node;
        }
        else {
            subtree[node] = 0;
        }

        return;
    }

    for (auto kid : kids[node]) {
        if (subtree[kid] > total / 2) {
            subtree[node] -= subtree[kid];
            calculate(kid);
            subtree[node] += subtree[kid];
            return;
        }
    }

    if (subtree[kids[node][0]] >= total / 4) {
        subtree[node] -= subtree[kids[node][0]];
        calculate(kids[node][0]);
        subtree[node] += subtree[kids[node][0]];
    }
    else {
        subtree[node] -= subtree[kids[node][1]];
        calculate(kids[node][1]);
        subtree[node] += subtree[kids[node][1]];
    }
}

void solve(void) {
    scanf("%d", &N);

    kids.assign(N, vector<int>());
    subtree.resize(N);
    depth.assign(N, 0);

    for (int i = 0; i < N - 1; i++) {
        int p;
        scanf("%d", &p);
        kids[p - 1].pb(i + 1);
    }

    d = 0;
    root = 0;
    total = 0;
    dfs(0);

    int mx = 0;
    for (int i = 0; i < N; i++) {
        mx = max(depth[i], mx);
    }

    int l = -1;
    int r = mx;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (query(0, mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    d = r;
    dfs(0);

    root = 0;
    total = subtree[0];
    while (total > 1) {
        calculate(root);
        total = subtree[root];
    }

    answer(root);

    printf("! %d\n", ans + 1);
    fflush(stdout);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}