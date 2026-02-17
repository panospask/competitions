#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

vector<int> query(int k) {
    printf("? %d\n", k);
    fflush(stdout);

    int x;
    vector<int> v;
    scanf("%d", &x);
    v.resize(x);
    for (int i = 0; i < x; i++) {
        scanf("%d", &v[i]);
        v[i]--;
    }

    reverse(v.begin(), v.end());
    return v;
}

int cnt = 1;

// Number of paths that start at node i
vector<int> total;
vector<pi> edges;

// The first path of current node is at cnt
void dfs(int node) {
    if (total[node] != -1) {
        cnt += total[node];
        return;
    }

    // We know that the first path (at position cnt) is just the node. We can safely skip it
    total[node] = -cnt;
    cnt++;

    while (true) {
        auto v = query(cnt);
        if (v.size() <= 1 || v[1] != node) {
            break;
        }
        edges.push_back(make_pair(node, v[0]));
        dfs(v[0]);
    }

    total[node] += cnt;
}

void solve(void) {
    int N;
    scanf("%d", &N);

    cnt = 1;
    total.assign(N, -1);
    edges.clear();

    for (int i = 0; i < N; i++) {
        dfs(i);
    }

    printf("! %d\n", (int)edges.size());
    for (auto [u, v] : edges) {
        printf("%d %d\n", u + 1, v + 1);
    }
    fflush(stdout);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}