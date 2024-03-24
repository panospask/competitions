#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N;
vector<vector<int>> adj_list;
vector<pi> edges;
int root, tot, cur;

deque<int> leafs;

void dfs(int node, int par)
{
    if (adj_list[node].size() == 1) {
        if (cur < tot / 2) {
            leafs.pb(node);
        }
        else {
            edges.pb(mp(leafs.front(), node));
            leafs.pop_front();

            if (leafs.empty()) {
                leafs.push_back(root);
            }
        }

        cur++;
    }

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            dfs(neigh, node);
        }
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    root = -1;
    tot = 0;
    for (int i = 0; i < N; i++) {
        if (adj_list[i].size() == 1) {
            root = i;
            tot++;
        }
    }

    dfs(root, -1);

    printf("%d\n", (int)edges.size());
    for (auto e : edges) {
        printf("%d %d\n", e.first + 1, e.second + 1);
    }

    return 0;
}