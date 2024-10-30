#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<vector<int>> adj_list;
priority_queue<pi, vector<pi>, greater<pi>> q;
vector<int> indeg;
vector<int> g;

int main(void)
{
    scanf("%d %d", &N, &M);

    g.resize(N);
    adj_list.resize(N);
    indeg.assign(N, 0);

    vector<int> order;
    for (int i = 0; i < N; i++) {
        scanf("%d", &g[i]);
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        indeg[v]++;
    }
    for (int i = 0; i < N; i++) {
        if (!indeg[i]) {
            q.push(mp(g[i], i));
        }
    }

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        order.pb(u);

        for (auto v : adj_list[u]) {
            indeg[v]--;
            if (!indeg[v]) {
                q.push(mp(g[v], v));
            }
        }
    }

    if (order.size() < N) {
        printf("-1\n");
    }
    else {
        for (int i = 0; i < N; i++) {
            printf("%d ", order[i] + 1);
        }
        printf("\n");
    }

    return 0;
}