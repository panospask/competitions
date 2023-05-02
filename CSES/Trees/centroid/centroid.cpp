#include <bits/stdc++.h>
#define pb push_back
#define mp make_pari
#define f first
#define s second

using namespace std;

int n;
vector<int> sz;
vector<vector<int>> adj_list;

int calc_size(int node, int par)
{
    sz[node] = 1;
    for (auto kid : adj_list[node])
        if (kid != par)
            sz[node] += calc_size(kid, node);

    return sz[node];
}

int find_centroid(int node, int par)
{
    for (auto kid : adj_list[node])
        if (kid != par && sz[kid] > n / 2)
            return find_centroid(kid, node);

    return node;
}

int main(void)
{
    scanf("%d", &n);
    adj_list.resize(n);
    sz.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    calc_size(0, -1);
    int cen = find_centroid(0, -1);

    printf("%d\n", cen + 1);
    return 0;
}