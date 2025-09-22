#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<vector<int>> S;
vector<int> cnt;

void solve(void) {
    scanf("%d %d", &N, &M);

    S.assign(N, vector<int>());
    cnt.assign(M, 0);
    for (int i = 0; i < N; i++) {
        int l;
        scanf("%d", &l);
        S[i].resize(l);

        for (int j = 0; j < l; j++) {
            scanf("%d", &S[i][j]);
            S[i][j]--;

            cnt[S[i][j]]++;
        }
    }

    bool covered = true;
    for (int v = 0; v < M; v++) {
        covered = covered && cnt[v] > 0;
    }

    int useless = 0;
    for (int i = 0; i < N; i++) {
        bool used = false;
        for (int j = 0; j < S[i].size(); j++) {
            if (cnt[S[i][j]] == 1) {
                used = true;
            }
        }

        if (!used) {
            useless++;
        }
    }

    if (covered && useless >= 2) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
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