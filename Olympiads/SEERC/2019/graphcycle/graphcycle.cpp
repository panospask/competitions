#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    for (int i = 0; i < N * (N - 1) / 2; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(w);
        adj_list[v].pb(w);
    }

    long long ans = 0;

    for (int i = 0; i < N; i++) {
        sort(adj_list[i].begin(), adj_list[i].end());

        for (int j = 1; j < adj_list[i].size(); j += 2) {
            ans += adj_list[i][j];
        }
    }

    printf("%lld\n", ans);

    return 0;
}