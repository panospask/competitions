#include <bits/stdc++.h>

#define pb push_back

using namespace std;

typedef long long ll;

int N;
vector<vector<int>> adj_list;
vector<int> subtree;

// total[i] is sum of subtrees of all nodes in subtree of i
vector<ll> total;
ll ans = 0;

void calculate(int node, int par) {
    subtree[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        calculate(neigh, node);
        subtree[node] += subtree[neigh];
        total[node] += total[neigh];
    }

    total[node] += subtree[node];
}

void reroot(int node, int par, ll par_ans) {
    // Calculate answer for this node
    ll cur_ans = par_ans;
    if (node != 0) {
        cur_ans -= subtree[node];
        cur_ans += N - subtree[node];
    }

    ans = max(ans, cur_ans);
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        reroot(neigh, node, cur_ans);
    }
}

int main(void) {
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    subtree.assign(N, 0);
    total.assign(N, 0);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    int root = 0;
    calculate(root, -1);

    reroot(root, -1, total[root]);

    printf("%lld\n", ans);
}