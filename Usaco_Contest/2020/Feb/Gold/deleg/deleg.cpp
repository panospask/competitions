#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int n;
vector<vector<int>> adj_list;
vector<bool> good;
vector<int> prnt;
vector<int> lonepath;

int findpath(int node, int par)
{
    int p = par != -1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        int res = findpath(neigh, node);
        if (res == -1)
            return -1;
        if (p > 1)
            return -1;

        p += res;
    }

    lonepath[node] = p;
    return p;
}

int dfs(int node, int par, int k)
{
    multiset<int> kidpaths;
    for (auto& neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        int res = dfs(neigh, node, k);
        if (res == -1)
            return -1;

        if (res != 0) {
            auto it = kidpaths.find(k - res);
            if (it != kidpaths.end()) {
                kidpaths.erase(it);
            }
            else {
                kidpaths.insert(res);
            }
        }
    }

    if (kidpaths.size() >= 2)
        return -1;

    int len = par != -1;
    if (kidpaths.size())
        len += *kidpaths.begin();

    return len % k;
}

int main(void)
{
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);

    int n;
    scanf("%d", &n);

    adj_list.resize(n);
    lonepath.assign(n, -1);
    good.assign(n, true);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    // findpath(0, -1);

    for (int k = 1; k <= n - 1; k++) {
        bool ans = false;
        if (good[k]) {
            if ((n - 1) % k == 0) {
                ans = dfs(0, -1, k) == 0;
            }

            if (!ans) {
                for (int i = 2 * k; i <= n - 1; i += k)
                    good[i] = false;
            }
        }
        if (ans)
            prnt.pb(1);
        else
            prnt.pb(0);
    }

    for (int i = 0; i < n - 1; i++)
        printf("%d", prnt[i]);
    printf("\n");

    return 0;
}