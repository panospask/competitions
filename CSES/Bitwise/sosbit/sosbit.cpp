#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int BITS = 20;

int N;
vector<int> x;

vector<int> subset, superset;

int main(void) {
    scanf("%d", &N);

    x.resize(N);
    subset.resize(1 << BITS);
    superset.resize(1 << BITS);
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);

        subset[x[i]]++;
        superset[x[i]]++;
    }

    for (int dim = 0; dim < BITS; dim++) {
        for (int mask = 0; mask < (1 << BITS); mask++) {
            if (CHECK_BIT(mask, dim)) {
                subset[mask] += subset[mask ^ (1 << dim)];
            }
        }
        for (int mask = (1 << BITS) - 1; mask >= 0; mask--) {
            if (!CHECK_BIT(mask, dim)) {
                superset[mask] += superset[mask ^ (1 << dim)];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        int mask = x[i];
        printf("%d %d %d\n", subset[mask], superset[mask], N - subset[(1 << BITS) - 1 - mask]);
    }

    return 0;
}