#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    sort(A.begin(), A.end());

    int prv = -1;
    int idx = 0;
    int ans = 0;
    vector<vector<int>> sequences;
    for (int i = 0; i < N; i++) {
        if (prv != A[i]) {
            idx = 0;
            prv = A[i];
        }

        while (true) {
            if (idx < sequences.size() && sequences[idx].back() == A[i]) {
                idx++;
            }
            else if (idx + 1 < sequences.size() && sequences[idx + 1].front() * 2 == A[i]) {
                idx++;
            }
            else {
                break;
            }
        }

        if (idx == sequences.size()) {
            sequences.pb({});
            ans++;
        }

        sequences[idx].pb(A[i]);
    }

    printf("%d\n", (int)sequences.size() - 1);
    for (int i = 0; i < sequences.size(); i++) {
        for (int j = 0; j < sequences[i].size(); j++) {
            printf("%d ", sequences[i][j]);
        }
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}