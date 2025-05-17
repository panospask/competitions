#include <bits/stdc++.h>

#define CHECK_BIT(var, pos) (((var) & (1 << (pos))) != 0)

using namespace std;

const int BITS = 30;

int N, K;
vector<int> A;

map<int, int> cnt[BITS];

void modify(int v, int s) {
    for (int b = 0; b < BITS; b++) {
        cnt[BITS - b - 1][v] += s;
        v >>= 1;
    }
}

int find(int v, int mask, int pos) {
    if (pos == -1) {
        return mask;
    }

    // Find bit pos of v
    int target = !(CHECK_BIT(v, pos));

    if (cnt[BITS - pos - 1][(mask << 1) + target]) {
        return find(v, (mask << 1) + target, pos - 1);
    }
    else {
        return find(v, (mask << 1) + !target, pos - 1);
    }
}

bool test(int len) {
    for (int b = 0; b < BITS; b++) {
        cnt[b].clear();
    }

    int best = 0;
    for (int i = 0; i < len - 1; i++) {
        modify(A[i], 1);
        best = max(best, A[i] ^ find(A[i], 0, BITS - 1));
    }


    for (int l = 0; l + len <= N; l++) {
        int r = l + len - 1;
        modify(A[r], 1);

        best = max(best, A[r] ^ find(A[r], 0, BITS - 1));

        modify(A[l], -1);
    }

    return best >= K;
}

void solve(void) {
    scanf("%d %d", &N, &K);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int l = 0;
    int r = N + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (test(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    if (r == N + 1) {
        printf("-1\n");
    }
    else {
        printf("%d\n", r);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}