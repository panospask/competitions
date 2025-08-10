#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;

void solve(void) {
    scanf("%d", &N);

    adj_list.assign(N, vector<int>());
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    if (N == 2) {
        printf("0\n");
        return;
    }

    int leafs = 0;
    for (int i = 0; i < N; i++) {
        leafs += adj_list[i].size() == 1;
    }

    int opt = 1;
    for (int i = 0; i < N; i++) {
        int cnt = 0;
        for (auto v : adj_list[i]) {
            cnt += adj_list[v].size() == 1;
        }

        opt = max(opt, cnt);
    }

    printf("%d\n", leafs - opt);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}