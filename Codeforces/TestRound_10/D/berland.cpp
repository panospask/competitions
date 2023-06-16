#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

int n, k;
int ans = INF;
int ansnode = -1;
vector<vector<int>> adj_list;
map<pi, int> edges;
vector<int> ansedges;

// dp[i][j]: Minimum number of closed roads s.t we are at city i with j cities contained in the region
vector<vector<int>> dp;
vector<vector<pi>> prv;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    dp[node][1] = adj_list[node].size() - 1;
    if (par == -1)
        dp[node][1]++;

    for (int i = 0; i < adj_list[node].size(); i++) {
        int neigh = adj_list[node][i];

        if (neigh == par)
            continue;

        vector<int> prevdp = dp[node];

        for (int j = 1; j <= k; j++) {
            if (dp[neigh][j] == INF)
                continue;

            for (int l = 1; l + j <= k; l++) {
                if (prevdp[l] == INF)
                    continue;

                if (dp[node][l + j] > dp[neigh][j] + prevdp[l] - 1) {
                    dp[node][l + j] = dp[neigh][j] + prevdp[l] - 1;
                    prv[node][l + j] = mp(neigh, j);
                }
            }

        }
        prevdp = dp[node];
    }

    if (ans > dp[node][k] + (par != -1)) {
        ans = dp[node][k] + (par != -1);
        ansnode = node;
    }
}

vector<bool> use(n);
void generate_edges(int node, int size)
{
    use[node] = false;
    while (size != 1) {
        int p_node, p_weight;
        tie(p_node, p_weight) = prv[node][size];

        size -= p_weight;

        generate_edges(p_node, p_weight);
    }

    for (auto neigh : adj_list[node]) {
        if (use[neigh])
            ansedges.push_back(edges[mp(neigh, node)]);
    }
}

int main(void)
{
    scanf("%d %d", &n, &k);

    adj_list.resize(n);
    use.assign(n, true);
    dp.assign(n, vector<int>(k + 1, INF));
    prv.assign(n, vector<pi>(k + 1, mp(-1, -1)));

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);

        edges[mp(a, b)] = i;
        edges[mp(b, a)] = i;
    }

    dfs(0, -1);

    generate_edges(ansnode, k);
    sort(ansedges.begin(), ansedges.end());
    printf("%d\n", ans);
    for (auto i : ansedges)
        printf("%d ", i + 1);
    printf("\n");
}