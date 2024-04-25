#include <bits/stdc++.h>

using namespace std;

const int A = 0;
const int B = 1;

struct dsu {
    vector<int> rep;
    vector<int> rank;

    void init(int N) {
        rep.resize(N);
        for (int i = 0; i < N; i++) {
            rep[i] = i;
        }
        rank.assign(N, 0);
    }

    int find(int a) {
        if (rep[a] == a) {
            return a;
        }
        return rep[a] = find(rep[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b) {
            return;
        }
        if (rank[a] < rank[b]) {
            swap(a, b);
        }
        if (rank[a] == rank[b]) {
            rank[a]++;
        }

        rep[b] = a;
    }
};

int N, a, b;
dsu graph;
unordered_map<int, int> pos;

// able[i]: 0 if cannot enter either set, 1 if can enter A, 2 if can enter B, 3 if can enter both
vector<int> able;

vector<int> chosen;

int main(void)
{
    scanf("%d %d %d", &N, &a, &b);
    able.assign(N, 0);
    graph.init(N);


    for (int i = 0; i < N; i++) {
        int p;
        scanf("%d", &p);

        pos[p] = i;
        if (pos.count(a - p)) {
            graph.unite(i, pos[a - p]);
            able[i] |= (1 << A);
            able[pos[a - p]] |= (1 << A);
        }
        if (pos.count(b - p)) {
            graph.unite(i, pos[b - p]);
            able[i] |= (1 << B);
            able[pos[b - p]] |= (1 << B);
        }
    }

    chosen.assign(N, (1 << A) | (1 << B));
    for (int i = 0; i < N; i++) {
        chosen[graph.find(i)] &= able[i];
    }
    for (int i = 0; i < N; i++) {
        if (chosen[i] == 0) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", min(chosen[graph.find(i)], 2) - 1);
    }
    printf("\n");

    return 0;
}