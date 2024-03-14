#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int n;
vector<vector<pi>> adj_list;
vector<int> first;
vector<int> p;
vector<int> drawnext;
vector<int> drawcur;
vector<bool> vis;

int rem = n;

void draw_edges_after(int node, int par, int time)
{
    vis[node] = true;
    p[node] = par;
    rem--;

    first[node] = lower_bound(adj_list[node].begin(), adj_list[node].end(), mp(time, INT_MAX)) - adj_list[node].begin();
    for (int i = first[node]; i < adj_list[node].size(); i++) {
        int nxt = adj_list[node][i].second;

        if (nxt == par)
            continue;

        draw_edges_after(nxt, node, adj_list[node][i].first);
    }

    // Add all the other edges in the next iteration
    if (first[node] != 0)
        drawnext.push_back(node);
}

void solve(void)
{
    adj_list.clear();
    p.clear();
    vis.clear();
    first.clear();

    scanf("%d", &n);

    adj_list.resize(n);
    vis.assign(n, false);
    first.resize(n);
    p.resize(n);
    drawcur.clear();
    drawnext.clear();
    rem = n;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(mp(i, b));
        adj_list[b].push_back(mp(i, a));
    }

    int ans = 0;
    first[0] = adj_list[0].size();
    drawcur.push_back(0);
    rem--;
    vis[0] = true;
    p[0] = -1;

    while (rem > 0) {
        for (auto& node : drawcur) {
            for (int i = 0; i < first[node]; i++) {
                if (adj_list[node][i].second == p[node])
                    continue;

                draw_edges_after(adj_list[node][i].second, node, adj_list[node][i].first);
            }
        }

        ans++;
        swap(drawcur, drawnext);
        drawnext.clear();
    }

    printf("%d\n", ans);
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