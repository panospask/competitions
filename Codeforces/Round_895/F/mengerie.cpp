#include <bits/stdc++.h>

#define pb push_back

using namespace std;

int N;
vector<int> dest, price;
vector<int> order;

vector<bool> visited;
vector<bool> on_cycle;
vector<bool> inside;

void dfs(int node)
{
    if (visited[node]) {
        if (on_cycle[node]) {
            int cost = price[node];
            int id = node;
            vector<int> cyc;

            inside[node] = true;
            cyc.pb(node);

            int v = dest[node];
            while (v != node) {
                if (cost > price[v]) {
                    cost = price[v];
                    id = v;
                }

                cyc.pb(v);
                inside[v] = true;
                v = dest[v];
            }

            reverse(cyc.begin(), cyc.end());

            int st = find(cyc.begin(), cyc.end(), id) - cyc.begin();
            for (int i = st; i != st + cyc.size(); i++)
                order.pb(cyc[i % (int)cyc.size()]);
        }

        return;
    }

    visited[node] = true;
    on_cycle[node] = true;

    dfs(dest[node]);

    on_cycle[node] = false;
    if (!inside[node])
        order.pb(node);

    return;
}

void solve(void)
{
    scanf("%d", &N);

    order.clear();
    visited.assign(N, false);
    inside.assign(N, false);
    on_cycle.assign(N, false);

    price.resize(N);
    dest.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &dest[i]);
        dest[i]--;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &price[i]);
    }

    for (int i = 0; i < N; i++)
        if (!visited[i])
            dfs(i);

    reverse(order.begin(), order.end());

    for (int i = 0; i < N; i++)
        printf("%d ", order[i] + 1);
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}