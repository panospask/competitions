#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;
vector<int> pref;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    pref.resize(N + 1);
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        pref[i + 1] = (pref[i] + A[i]) % 3;
    }

    for (int l = 0; l - 2 < N; l++) {
        int s1 = pref[l + 1];

        for (int r = l + 1; r < N; r++) {
            int s2 = pref[r + 1] - pref[l + 1];
            int s3 = pref[N] - pref[r + 1];

            s2 = (s2 % 3 + 3) % 3;
            s3 = (s3 % 3 + 3) % 3;

            if ((s1 == s2 && s2 == s3) || (s1 != s2) && (s1 != s3) && (s2 != s3)) {
                printf("%d %d\n", l + 1, r + 1);
                return;
            }
        }
    }

    printf("0 0\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}