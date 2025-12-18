#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)

using namespace std;

const int BITS = 30;

int N;
vector<int> basis;
int cnt = 0;

void insert(int mask) {
    for (int b = BITS - 1; b >= 0; b--) {
        if (CHECK_BIT(mask, b) == false) {
            continue;
        }

        if (basis[b] == 0) {
            // No way to find mask => must be inserted into basis
            basis[b] = mask;
            cnt++;
            return;
        }
            
        mask ^= basis[b];
    }
}

int find(int k) {
    int rem = cnt;
    int ans = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        if (basis[b] == 0) {
            continue;
        }

        rem--;

        int createone = false;
        if ((1 << rem) < k) {
            // We need to create one
            createone = true;
            k -= (1 << rem);
        }

        if (CHECK_BIT(ans, b) ^ createone) {
            ans = ans ^ basis[b];
        }
    }

    return ans;
}

int main(void) {
    scanf("%d", &N);

    basis.assign(BITS, 0);
    for (int i = 0; i < N; i++) {
        int t, k;
        scanf("%d %d", &t, &k);

        if (t == 1) {
            insert(k);
        }
        else {
            printf("%d\n", find(k));
        }
    }

    return 0;
}