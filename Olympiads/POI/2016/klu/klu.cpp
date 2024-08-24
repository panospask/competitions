#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

int N;
vector<vector<int>> adj_list;
vector<int> couple;
vector<int> pos;

bool brute(int node, int p)
{
    if (pos[node] != -1) {
        return false;
    }

    pos[node] = p;
    if (p == (1 << N) - 1) {
        return __builtin_popcount(node) == 1;
    }

    for (int b = 0; b < N; b++) {
        int neigh = node ^ (1 << b);
        if (pos[neigh] == -1) {
            pos[neigh] = p + 1;
            if (brute(couple[neigh], p + 2)) {
                return true;
            }
            pos[neigh] = -1;
        }
    }

    pos[node] = -1;

    return false;
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(1 << N);
    couple.resize(1 << N);
    pos.assign(1 << N, -1);

    for (int i = 0; i < 1 << (N - 1); i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        couple[u] = v;
        couple[v] = u;
    }

    pos[0] = 0;
    if (brute(couple[0], 1) == false) {
        printf("NIE\n");
        return 0;
    }

        vector<int> a(1 << N);
        for (int i = 0; i < (1 << N); i++) {
            a[pos[i]] = i;
        }
        for (int i = 0; i < (1 << N); i++) {
            printf("%d ", a[i]);
        }
        printf("\n");

    return 0;
}