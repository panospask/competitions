#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> p;

int main(void) {
    scanf("%d", &N);

    p.resize(N - 1);
    for (int i = 0; i < N - 1; i++) {
        p[i] = i;
    }
    next_permutation(p.begin(), p.end() - 1);

    printf("%d\n", N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        
        if (u != 0) {
            u = p[u - 1] + 1;
        }
        if (v != 0) {
            v = p[v - 1] + 1;
        }

        printf("%d %d\n", u + 1, v + 1);
    }
}