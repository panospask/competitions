#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;

int cnt[100005];
long long dp[100005];

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);

        cnt[A[i]]++;
    }


    dp[1] = cnt[1];
    for (int i = 2; i <= 100000; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + (long long)i * cnt[i]);
    }

    printf("%lld\n", dp[100000]);
}