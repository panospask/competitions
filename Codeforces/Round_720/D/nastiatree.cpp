#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

int n;
vector<vector<int>> adj_list;
map<pi, bool> removed;
vector<bool> visited;
vector<bool> par_rm;
vector<pi> rm;
vector<pi> addedge;
pi add;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;
        dfs(neigh, node);
    }

    int cnt = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;
        if (par_rm[neigh])
            continue;

        cnt++;
    }

    if (cnt >= 2) {
        if (par != -1) {
            par_rm[node] = true;
            rm.pb(mp(node, par));

            removed[mp(node, par)] = removed[mp(par, node)] = true;
        }
        if (cnt >= 3) {
            for (int i = 0; i < adj_list[node].size() && cnt >= 3; i++) {
                int neigh = adj_list[node][i];

                if (neigh == par || par_rm[neigh])
                    continue;

                par_rm[neigh] = true;
                rm.pb(mp(neigh, node));
                removed[mp(neigh, node)] = true;
                removed[mp(node, neigh)] = true;
                cnt--;
            }
        }
    }
}

void dfs2(int node, int par)
{
    visited[node] = true;
    int cnt = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh != par && !removed[mp(neigh, node)]) {
            cnt++;
            dfs2(neigh, node);
        }
    }

    if (cnt == 0) {
        if (par == -1)
            add.f = add.s = node;
        if (add.first == -1)
            add.first = node;
        else
            add.second = node;
    }
    else if (par == -1 && cnt == 1) {
        if (add.first == -1)
            add.first = node;
        else
            add.second = node;
    }
}

void solve(void)
{
    adj_list.clear();
    par_rm.clear();
    rm.clear();
    addedge.clear();
    removed.clear();
    visited.clear();

    scanf("%d", &n);

    par_rm.resize(n);
    adj_list.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    dfs(0, -1);

    visited.assign(n, false);

    int p_s = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            add = mp(-1, -1);
            dfs2(i, -1);

            if (p_s != -1)
                addedge.push_back(mp(p_s, add.f));
            p_s = add.s;
        }
    }

    printf("%d\n", (int)rm.size());
    for (int i = 0; i < rm.size(); i++) {
        printf("%d %d %d %d\n", rm[i].f + 1, rm[i].s + 1, addedge[i].f + 1, addedge[i].s + 1);
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}