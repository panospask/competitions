#include <bits/stdc++.h>

using namespace std;

int N, K, M;
vector<vector<int>> adj_list;

vector<int> run;

int main(void)
{
    scanf("%d %d %d", &N, &K, &M);

    adj_list.resize(N);
    run.assign(N, 0);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
    }

    for (int i = 0; i < N * K; i++) {
        int c;
        scanf("%d", &c);
        c--;

        run[c]++;
        printf("%d ", run[c]);
    }
    printf("\n");

    return 0;
}