#include <bits/stdc++.h>

using namespace std;

int N, M, L;
vector<int> A;

void solve(void) {
    scanf("%d %d %d", &N, &M, &L);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        A[i]--;
    }

    multiset<int> values;
    for (int i = 0; i < min(N + 1, M); i++) {
        values.insert(0);
    }

    int p = 0;
    for (int i = 0; i < L; i++) {
        int v = *values.begin();
        values.erase(values.begin());
        values.insert(v + 1);

        if (p < N && A[p] == i) {
            int v = *values.rbegin();
            values.erase(values.find(v));
            p++;

            if (values.size() <= N - p) {
                values.insert(0);
            }
        }
    }

    printf("%d\n", *values.begin());
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}