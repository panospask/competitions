#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<int> indeg;
vector<int> outdeg;
vector<vector<int>> adj_list, revlist;
vector<int> l, r;

int main(void) {
    scanf("%d %d", &N, &M);

    indeg.resize(N);
    outdeg.resize(N);
    adj_list.resize(N);
    revlist.resize(N);
    l.resize(N);
    r.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        revlist[v].pb(u);
        outdeg[u]++;
        indeg[v]++;
    }

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &l[i], &r[i]);
        l[i]--; r[i]--;
    }

    queue<int> q;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (outdeg[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cnt++;

        for (auto u : revlist[v]) {
            r[u] = min(r[u], r[v] - 1);
            outdeg[u]--;
            if (outdeg[u] == 0) {
                q.push(u);
            }
        }
    }
    if (cnt < N) {
        printf("No\n");
        return 0;
    }

    priority_queue<pi, vector<pi>, greater<pi>> q2;
    vector<vector<int>> by_l(N);
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0) {
            by_l[l[i]].pb(i);
        }
    }
    vector<int> ans(N);

    for (int t = 0; t < N; t++) {
        for (auto u : by_l[t]) {
            q2.push(mp(r[u], u));
        }

        if (q2.empty()) {
            printf("No\n");
            return 0;
        }

        int u = q2.top().second;
        q2.pop();
        ans[u] = t;
        if (t > r[u]) {
            printf("No\n");
            return 0;
        }

        for (auto v : adj_list[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                if (l[v] <= t) {
                    q2.push(mp(r[v], v));
                }
                else {
                    by_l[l[v]].pb(v);
                }
            }
        }
    }

    printf("Yes\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");

    return 0;
}