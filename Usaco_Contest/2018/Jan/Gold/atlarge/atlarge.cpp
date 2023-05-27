#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int n, k;
vector<vector<int>> adj_list;
vector<int> leafs;
vector<int> leafdist;
vector<int> bessiedist;

void calc_leafdist(void)
{
    queue<int> to_proccess;
    leafdist.assign(n, -1);

    for (auto leaf : leafs) {
        to_proccess.push(leaf);
        leafdist[leaf] = 0;
    }

    while (!to_proccess.empty()) {
        int v = to_proccess.front();
        to_proccess.pop();

        for (auto neigh : adj_list[v]) if (leafdist[neigh] == -1) {
            leafdist[neigh] = leafdist[v] + 1;
            to_proccess.push(neigh);
        }
    }
}

int calc_farmers_needed(int node, int par, int b)
{
    bessiedist[node] = b;
    if (bessiedist[node] >= leafdist[node])
        return 1;

    // If not, it is not leaf
    int ans = 0;
    for (auto neigh : adj_list[node]) if (neigh != par)
        ans += calc_farmers_needed(neigh, node, b +1);

    return ans;
}

int main(void)
{
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);

    scanf("%d %d", &n, &k);
    k--;

    adj_list.resize(n);
    leafdist.assign(n, -1);
    bessiedist.assign(n, -1);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    for (int i = 0; i < n; i++)
        if (adj_list[i].size() == 1)
            leafs.push_back(i);

    calc_leafdist();
    int ans = calc_farmers_needed(k, -1, 0);

    printf("%d\n", ans);
    return 0;
}