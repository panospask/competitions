#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1LL << pos))

using namespace std;

int N;
vector<int> A;
map<int, int> cnt;

map<int, bool> checked;
vector<int> bits;

int S = 0;

void check(int v) {
    if (checked[v]) {
        S = 2;
        return;
    }
    checked[v] = true;
    if (cnt[v] % 2 == 0) {
        return;
    }
    else {
        int m = 0;
        for (int b = 0; b < 30; b++) {
            if (CHECK_BIT(v, b)) {
                if (bits[b] != cnt[v]) {
                    m = m + (1 << b);
                }
            }
        }

        if (cnt[m] == 0) {
            S++;
        }
        else {
            check(m);
        }
    }
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    cnt.clear();
    bits.assign(30, 0);
    checked.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        cnt[A[i]]++;

        for (int b = 0; b < 30; b++) {
            if (CHECK_BIT(A[i], b)) {
                bits[b]++;
            }
        }
    }

    sort(A.begin(), A.end());
    A.resize(unique(A.begin(), A.end()) - A.begin());

    for (int i = 0; i < A.size(); i++) {
        if (!checked[A[i]]) {
            check(A[i]);
        }
    }

    if (S == 1) {
        printf("Menji\n");
    }
    else {
        printf("Bot\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}