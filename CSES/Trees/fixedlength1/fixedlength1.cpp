#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int level = 0;
int n, k;
int mx_d = 0;
vector<int> subtree;
vector<vector<int>> adj_list;
vector<bool> removed;
int id = -1;
int total[200000 + 5];
ll ans = 0;

int sbtree(int node, int par, int d, bool first)
{
    mx_d = max(mx_d, d);
    if (d > k && first)
        return 0;
    // cout << "CHECK NODE " << node << endl;
    subtree[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh != par && !removed[neigh])
            subtree[node] += sbtree(neigh, node, d + 1, first);
    }

    if (d <= k) {
        if (first)
            ans += total[k - d];
        else if (d < k)
            total[d]++;
    }

    return subtree[node];
}

int find_centroid(int node, int par, int treesize)
{
    for (auto neigh : adj_list[node]) {
        if (neigh != par && !removed[neigh] && subtree[neigh] * 2 > treesize)
            return find_centroid(neigh, node, treesize);
    }

    return node;
}

void decompose(int node)
{
    // cout << level << endl;
    int centroid = find_centroid(node, -1, subtree[node]);

    mx_d = 0;
    removed[centroid] = true;
    total[0] = 1;
    for (auto neigh : adj_list[centroid]) {
        if (!removed[neigh]) {
            sbtree(neigh, centroid, 1, true);
            sbtree(neigh, centroid, 1, false);
        }
    }

    memset(total, 0, (mx_d + 1) * sizeof(int));
    for (auto v : adj_list[centroid]) {
        if (!removed[v])
            decompose(v);
    }
}

int main(void)
{
    scanf("%d %d", &n, &k);
    adj_list.resize(n);
    subtree.resize(n);
    removed.assign(n, false);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    sbtree(0, -1, 0, true);
    decompose(0);

    printf("%lld\n", ans);

    return 0;
}