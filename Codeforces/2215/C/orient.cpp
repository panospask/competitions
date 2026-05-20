#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)

using namespace std;

int N, S;

void encode(void) {
    scanf("%d %d", &N, &S);
    S--;

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        if (u > v) {
            swap(u, v);
        }

        int sum = 0;
        for (int j = u; j < v; j++) {
            sum ^= CHECK_BIT(S, j);
        }

        if (sum == 0) {
            printf("%d %d\n", u, v);
        }
        else {
            printf("%d %d\n", v, u);
        }
        fflush(stdout);
    }
}

bool check(int S, vector<pair<int, int>>& edges) {
    for (auto [u, v] : edges) {
        int res = 0;
        if (u > v) {
            swap(u, v);
            res = 1;
        }
        int sum = 0;
        for (int j = u; j < v; j++) {
            sum ^= CHECK_BIT(S, j);
        }

        if (res != sum) {
            return false;
        }
    }

    return true;
}

void decode(void) {
    scanf("%d", &N);
    S = 0;

    vector<pair<int, int>> edges;
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        edges.push_back({u, v});
    }

    while (true) {
        if (check(S, edges)) {
            break;
        }

        S++;
    }

    printf("%d\n", S);
}

int main(void) {
    int t, Q;

    scanf("%d %d", &t, &Q);

    while (t--) {
        if (Q == 1) {
            encode();
        }
        else {
            decode();
        }
    }
}