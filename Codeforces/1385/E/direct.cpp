#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int ,int> pi;

int N, M;
vector<vector<int>> adj_list;
vector<int> indeg;
vector<int> order;
vector<pi> edges;

void solve(void)
{
    scanf("%d %d", &N, &M);

    indeg.assign(N, 0);
    order.resize(N);
    adj_list.assign(N, vector<int>());
    edges.resize(M);

    for (int i = 0; i < M; i++) {
        int u, v, d;
        scanf("%d %d %d", &d, &u, &v);
        u--; v--;

        edges[i] = mp(u, v);
        if (d) {
            adj_list[u].pb(v);
            indeg[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (!indeg[i]) {
            q.push(i);
        }
    }

    int cnt = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        order[u] = cnt++;

        for (auto v : adj_list[u]) {
            indeg[v]--;
            if (!indeg[v]) {
                q.push(v);
            }
        }
    }

    if (cnt != N) {
        printf("NO\n");
        return;
    }

    printf("YES\n");
    for (int i = 0; i < M; i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        if (order[u] > order[v]) {
            swap(u, v);
        }

        printf("%d %d\n", u + 1, v + 1);
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}