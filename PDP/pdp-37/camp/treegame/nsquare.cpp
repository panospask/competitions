#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, R, K, L;

ll ans = 0;
vector<int> A;
vector<vector<int>> adj_list;

vector<int> cnt;
vector<ll> subtree;

vector<int> p;

int counter = 0;
vector<int> tin, tout;

void dfs(int node, int par) {
    cnt[node] = 1;
    subtree[node] = A[node];
    p[node] = par;

    tin[node] = counter++;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];
        cnt[node] += cnt[neigh];

    }

    tout[node] = counter;
}

void upwards(int node, int v) {
    if (node == R) {
        return;
    }

    if (v + L >= cnt[node] && v <= K) {
        ans = max(ans, subtree[node]);
    }
    if (v + K >= cnt[node] && v <= L) {
        ans = max(ans, subtree[node]);
    }

    upwards(p[node], v);
}

bool ancestor(int i, int j) {
    if (tin[i] > tin[j]) {
        swap(i, j);
    }

    return tin[i] <= tin[j] && tout[i] >= tout[j];
}

int main(void) {
    scanf("%d %d %d %d", &N, &R, &K, &L);
    R--;

    adj_list.resize(N);
    A.resize(N);
    subtree.resize(N);
    cnt.resize(N);
    p.resize(N);
    tin.resize(N);
    tout.resize(N);
    counter = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(R, -1);

    // Nested
    ans = 0;
    for (int i = 0; i < N; i++) {
        upwards(i, cnt[i]);
    }

    // Not nested
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == R || j == R) {
                continue;
            }

            if ((cnt[i] <= K && cnt[j] <= L) || (cnt[j] <= K && cnt[i] <= L)) {
                if (!ancestor(i, j)) {
                    ans = max(ans, subtree[i] + subtree[j]);
                }
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}