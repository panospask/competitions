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
vector<vector<vector<int>>> dp;
vector<vector<vector<pi>>> prv;

void dfs(int node, int par)
{
    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    int ttl = adj_list[node].size() + 1;
    dp[node].assign(ttl, vector<int>(k + 1, INF));
    prv[node].assign(ttl, vector<pi>(k + 1, mp(-1, -1)));

    dp[node][0][1] = adj_list[node].size() - 1;
    if (par == -1)
        dp[node][0][1]++;

    for (int i = 0; i < adj_list[node].size(); i++) {
        int neigh = adj_list[node][i];

        dp[node][i + 1] = dp[node][i];
        prv[node][i + 1] = prv[node][i];
        if (neigh == par) {
            continue;
        }

        int tot = adj_list[neigh].size();
        for (int j = 1; j <= k; j++) {
            if (dp[neigh][tot][j] == INF)
                continue;

            for (int l = 1; l + j <= k; l++) {
                if (dp[node][i][l] == INF)
                    continue;

                if (dp[node][i + 1][l + j] > dp[neigh][tot][j] + dp[node][i][l] - 1) {
                    dp[node][i + 1][l + j] = dp[neigh][tot][j] + dp[node][i][l] - 1;
                    prv[node][i + 1][l + j] = mp(neigh, j);
                }
            }

        }
    }

    if (ans > dp[node][ttl - 1][k] + (par != -1)) {
        ans = dp[node][ttl - 1][k] + (par != -1);
        ansnode = node;
    }
}

vector<bool> use;
void generate_edges(int node, int size)
{
    use[node] = false;

    int idx = adj_list[node].size();

    while (size != 1) {
        int p_node, p_size;
        tie(p_node, p_size) = prv[node][idx][size];

        idx = lower_bound(adj_list[node].begin(), adj_list[node].end(), p_node) - adj_list[node].begin();

        generate_edges(p_node, p_size);
        size -= p_size;
    }

    for (auto neigh : adj_list[node])
        if (use[neigh]) {
            ansedges.push_back(edges[mp(node, neigh)]);
        }
}

int main(void)
{
    scanf("%d %d", &n, &k);

    adj_list.resize(n);
    dp.resize(n);
    prv.resize(n);
    use.assign(n, true);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);

        edges[mp(a, b)] = i;
        edges[mp(b, a)] = i;
    }
    for (int i = 0; i < n; i++)
        sort(adj_list[i].begin(), adj_list[i].end());

    dfs(0, -1);

    generate_edges(ansnode, k);

    printf("%d\n", ans);
    sort(ansedges.begin(), ansedges.end());
    for (auto e : ansedges)
        printf("%d ", e + 1);
    printf("\n");

    return 0;
}