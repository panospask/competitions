#include <bits/stdc++.h>
#define pb push_back
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

int N, M, K;

vector<vector<int>> adj_list;
vector<bool> visited;
vector<int> dep;

vector<int> p[2];
vector<int> ans;

bool dfs(int node, int par, int d)
{
    if (visited[node]) {
        return dep[node] % 2 == d % 2;
    }
    
    visited[node] = true;
    dep[node] = d;
    p[d % 2].pb(node);

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        if (!dfs(neigh, node, d + 1)) {
            return false;
        }
    }

    return true;
}

void negative(void)
{
    printf("NIE\n");
    exit(0);
}

void brute(void)
{
    int opt = -1;
    vector<int> cur;

    for (int mask = 1; mask < (1 << N); mask++) {
        queue<int> q;

        cur.assign(N, -1);
        bool good = true;

        for (int i = 0; i < N; i++) {
            if (CHECK_BIT(mask, i)) {
                cur[i] = 0;
                q.push(i);
            }
        }

        while (!q.empty() && good) {
            int u = q.front();
            q.pop();

            for (auto v : adj_list[u]) {
                if (cur[v] == -1) {
                    cur[v] = cur[u] + 1;
                    if (cur[v] >= K) {
                        cur[v] -= 2;
                    }

                    q.push(v);
                }
                else {
                    if (abs(cur[v] - cur[u]) != 1) {
                        good = false;
                        break;
                    }
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (cur[i] == -1) {
                good = false;
            }
        }

        if (good) {
            int res = 0;
            for (int i = 0; i < N; i++) {
                res += cur[i] == 0 || cur[i] == K - 1;
            }

            if (res > opt) {
                ans = cur;
                opt = res;
            }
        }
    }

    if (opt == -1) {
        negative();
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &K);

    adj_list.resize(N);
    visited.assign(N, false);
    dep.assign(N, 0);
    ans.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    if (N <= 20) {
        brute();
    }
    else {
        for (int i = 0; i < N; i++) {
            if (visited[i]) {
                continue;
            }

            if (!dfs(i, i, 0)) {
                negative();
            }

            if (p[0].size() < p[1].size()) {
                swap(p[0], p[1]);
            }
            for (int k = 0; k < 2; k++) {
                for (auto j : p[k]) {
                    ans[j] = k;
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
        res += ans[i] == 0 || ans[i] == K - 1;
    }

    printf("%d\n", res);
    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i] + 1);
    }
    printf("\n");

    return 0;
}