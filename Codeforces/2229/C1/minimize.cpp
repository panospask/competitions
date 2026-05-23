#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    vector<int> operations;
    for (int i = N - 1; i >= 0; i--) {
        if ((A[i] < 0) ^ (operations.size() % 2 == 0)) {
            operations.push_back(i + 1);
        }
    }

    printf("%d\n", (int)operations.size());
    for (auto i : operations) {
        printf("%d ", i);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}