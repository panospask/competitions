#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<vector<pi>> adj_list;
vector<bool> visited;
vector<int> status;
int ans = 0;

bool bfs(int s)
{
    int c[2] = {0, 0};
    status[s] = 0;

    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        c[status[u]]++;

        for (auto [v, t] : adj_list[u]) {
            int new_status = status[u] ^ t;

            if (visited[v]) {
                if (new_status != status[v]) {
                    return false;
                }
            }
            else {
                visited[v] = true;
                status[v] = new_status;
                q.push(v);
            }
        }
    }

    ans += max(c[0], c[1]);

    return true;
}

void solve(void)
{
    visited.clear();
    status.clear();
    adj_list.clear();
    ans = 0;

    scanf("%d %d", &N, &M);

    visited.assign(N, false);
    adj_list.resize(N);
    status.resize(N);

    for (int i = 0; i < M; i++) {
        int t, u, v;
        scanf("%d %d %d", &t, &u, &v);
        u--; v--;
        t %= 2;

        adj_list[u].pb(mp(v, t));
        adj_list[v].pb(mp(u, t));
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            bool good = bfs(i);
            if (!good) {
                printf("-1\n");
                return;
            }
        }
    }

    printf("%d\n", ans);
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