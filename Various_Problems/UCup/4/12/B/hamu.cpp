#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, M, s;
vector<vector<int>> adj_list;

int main(void) {
    scanf("%d %d", &N, &M);
    
    adj_list.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
}