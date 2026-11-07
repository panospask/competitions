#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> A, B;
map<int, int> m1;
map<int, int> m2;

int main(void) {
    scanf("%d", &N);
    int ans = 0;
    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        m1[A[i]]++;

        ans = max(ans, min(2, min(m1[A[i]], m2[A[i]])));
    }
    scanf("%d", &M);
    B.resize(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &B[i]);
        m2[B[i]]++;

        ans = max(ans, min(2, min(m1[B[i]], m2[B[i]])));
    }

    // Length 2 is vacuously true since there are no alternatives...

    /* dp(i)[j][s]: What is the longest commong zigzag subsequence (s true iff the last step is increasing)
     * that ends in some i'<= i and exactly at j (therefore I know the value of the last element, b[j])
     */
    vector<vector<int>> dp(M, vector<int>(2, 0));
    for (int i = 0; i < N; i++) {
        // The best **usable** increasing or decreasing subsequence before current j
        // We know for a fact that if we are to currently extend some subsequence, it will be with an element of value a[i]
        int biggest[2] = {0, 0};
        biggest[0] = 0;
        biggest[1] = 0;
        for (int j = 0; j < M; j++) {
            if (A[i] < B[j]) {
                // We can make a decreasing subsequence by using A[i]==B[j']<B[j] for some later j'
                // Use the increasing ending here
                biggest[0] = max(biggest[0], dp[j][1]);
            }
            else if (A[i] > B[j]) {
                biggest[1] = max(biggest[1], dp[j][0]);
            }
            else {
                dp[j][0] = max(dp[j][0], biggest[0] + 1);
                dp[j][1] = max(dp[j][1], biggest[1] + 1);
            }
            ans = max(ans, max(dp[j][0], dp[j][1]));
        }
    }
    printf("%d\n", ans);
}