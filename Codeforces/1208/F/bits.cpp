#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int BITS = 21;

typedef pair<int, int> pi;

int N;
vector<int> A;
vector<pi> superset;

void insert(pi& a, int b) {
    if (b > a.first) {
        swap(b, a.first);
    }
    if (b > a.second) {
        swap(b, a.second);
    }
}

void merge(pi& a, pi b) {
    pi res = a;
    insert(a, b.first);
    insert(a, b.second);
}

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    superset.resize(1 << BITS);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        merge(superset[A[i]], {i, 0});
    }

    for (int b = 0; b < BITS; b++) {
        for (int mask = (1 << BITS) - 1; mask >= 0; mask--) {
            if (CHECK_BIT(mask, b) == 0) {
                merge(superset[mask], superset[mask + (1 << b)]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N - 2; i++) {
        int opt = 0;
        for (int b = BITS; b >= 0; b--) {
            if (CHECK_BIT(A[i], b)) {
                continue;
            }

            pi res = superset[opt + (1 << b)];
            if (res.second > i) {
                opt = opt + (1 << b);
            }
        }

        ans = max(ans, A[i] | opt);
    }

    printf("%d\n", ans);
}