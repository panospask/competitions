#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K, M;
vector<vector<int>> A;

int main(void) {
    scanf("%d %d %d", &N, &M, &K);

    A.resize(N, vector<int>(K));
    for (int j = 0; j < K; j++) {
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i][j]);
        }
    }
    ll used = 0;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        sort(A[i].begin(), A[i].end());
        used += A[i][K / 2];

        for (int j = 0; j < K; j++) {
            ans += abs(A[i][j] - A[i][K / 2]);
        }
    }

    int idx = K / 2;
    if (used < M) {
        while (used < M) {
            for (int i = 0; i < N && used < M; i++) {
                int mv = min((ll)A[i][idx + 1] - A[i][idx], M - used);

                // People from idx and below gain, people from idx + 1 and above lose
                int mul = (idx + 1 - (K - (idx + 1)));
                ans += (ll)mul * mv;
                used += mv;
            }
            idx++;
        }
    }
    else {
        while (used > M) {
            for (int i = 0; i < N && used > M; i++) {
                int mv = min((ll)A[i][idx] - A[i][idx - 1], used - M);

                // People from idx and above gain, people from idx - 1 and below lose
                int mul = ((K - idx) - idx);
                ans += (ll)mul * mv;
                used -= mv;
            }
            idx--;
        }
    }

    printf("%lld\n", ans / 2);
}