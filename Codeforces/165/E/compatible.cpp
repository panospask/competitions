#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int BITS = 22;

int N;
vector<int> A;
vector<int> subset;

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    subset.assign(1 << BITS, -1);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        subset[A[i]] = A[i];
    }

    for (int dim = 0; dim < BITS; dim++) {
        for (int mask = 0; mask < (1 << (BITS)); mask++) {
            if (CHECK_BIT(mask, dim)) {
                subset[mask] = max(subset[mask], subset[mask - (1 << dim)]);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        int mask = A[i];
        printf("%d ", subset[(1 << BITS) - 1 - mask]);
    }
    printf("\n");
}