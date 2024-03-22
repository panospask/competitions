#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<vector<int>> adj_list;
int good_components;

int cut_sub(int node, int par, int tar)
{
    int tot = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        tot += cut_sub(neigh, node, tar);
    }

    if (tot >= tar) {
        good_components++;
        tot = 0;
    }

    return tot;
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    adj_list.assign(N, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    int l = 0; // cut_sub(0, -1, l) >= K + 1
    int r = N + 1; // cut_sub(0, -1, r) < K + 1

    while (l < r - 1) {
        int mid = (l + r) / 2;

        good_components = 0;
        cut_sub(0, -1, mid);
        if (good_components < K + 1) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    printf("%d\n", l);
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