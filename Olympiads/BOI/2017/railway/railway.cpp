#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n, m, k;
vector<vector<ii>> adj_list;
vector<vector<int>> ancestor;
vector<int> depth;
vector<int> st;
vector<ii> range;
vector<int> en;
vector<int> ans;
int cnt = 0;

int jump(int x, int levels)
{
    for (int i = 0; i < 20; i++)
        if (levels & (1 << i))
            x = ancestor[i][x];

    return x;
}

int find_lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);

    a = jump(a, depth[a] - depth[b]);
    if (a == b)
        return a;

    for (int i = 19; i >= 0; i--) {
        if (ancestor[i][a] != ancestor[i][b]) {
            a = ancestor[i][a];
            b = ancestor[i][b];
        }
    }

    return ancestor[0][a];
}

void dfs(int node, int par)
{
    range[node].first = cnt++;
    ancestor[0][node] = par;
    depth[node] = depth[par] + 1;
    for (auto neigh : adj_list[node])
        if (neigh.first != par)
            dfs(neigh.first, node);

    range[node].second = cnt;
}

int calc_ans(int node)
{
    int ttl_tracks = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh.first != ancestor[0][node]) {
            int upcoming = calc_ans(neigh.first);
            if (upcoming >= k)
                ans.push_back(neigh.second);
            ttl_tracks += upcoming;
        }
    }

    return ttl_tracks + st[node] - en[node];
}

int main(void)
{
    scanf("%d %d %d", &n, &m, &k);
    adj_list.resize(n + 1);
    depth.resize(n + 1);
    st.resize(n + 1);
    en.resize(n + 1);
    range.resize(n + 1);
    ancestor.resize(20, vector<int>(n + 1));
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj_list[a].push_back(mp(b, i+1));
        adj_list[b].push_back(mp(a, i+1));
    }

    depth[0] = -1;
    dfs(1, 0);

    for (int up = 1; up < 20; up++)
        for (int i = 1; i <= n; i++)
            ancestor[up][i] = ancestor[up-1][ancestor[up-1][i]];

    vector<int> a;
    for (int i = 0; i < m; i++) {
        int s;
        scanf("%d", &s);
        a.resize(s);
        for (int j = 0; j < s; j++) {
            scanf("%d", &a[j]);
            st[a[j]]++;
        }

        int lca = a[0];
        ii cur = range[a[0]];
        for (int j = 1; j < s; j++) {
            ;
        }

        en[lca] += s;
    }

    calc_ans(1);
    sort(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (auto t : ans) {
        printf("%d ", t);
    }
    printf("\n");

    return 0;
}