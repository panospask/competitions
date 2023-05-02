#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> adj_list;
vector<int> subtree;
vector<bool> removed;
vector<int> c_par;
vector<int> ranking;

int calc_subtree(int node, int par = -1)
{
    subtree[node] = 1;
    for (auto kid : adj_list[node])
        if (kid != par && !removed[kid])
            subtree[node] += calc_subtree(kid, node);

    return subtree[node];
}

int find_centroid(int node, int par, int treesize)
{
    for (auto kid : adj_list[node])
        if (kid != par && !removed[kid] && subtree[kid] * 2 > treesize)
            return find_centroid(kid, node, treesize);

    return node;
}

bool centroid_decompose(int node, int cent_par, int level)
{
    if (level >= 26)
        return false;

    int centroid = find_centroid(node, -1, calc_subtree(node));
    ranking[centroid] = level;

    removed[centroid] = true;
    c_par[centroid] = cent_par;
    bool isgood = true;
    for (auto kid : adj_list[centroid])
        if (!removed[kid] && kid != cent_par)
            isgood = isgood && centroid_decompose(kid, centroid, level + 1);

    return isgood;
}

int main(void)
{
    scanf("%d", &n);
    adj_list.resize(n);
    subtree.resize(n);
    c_par.resize(n);
    removed.assign(n, false);
    ranking.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    bool ans = centroid_decompose(0, -1, 0);
    if (ans) {
        for (int i = 0; i < n; i++)
            printf("%c ", ranking[i] + 'A');
    }
    else
        printf("Impossible!");
    printf("\n");

    return 0;
}