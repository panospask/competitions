#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> A;
vector<int> v;

int find(int x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin();
}

int main(void) {
    scanf("%d", &N);

    A.resize(N + 1);
    A[0] = 0;
    v.push_back(0);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        v.push_back(A[i]);
    }
    v.resize(unique(v.begin(), v.end()) - v.begin());
    sort(v.begin(), v.end());

    vector<vector<int>> dp(N + 1, vector<int>(v.size(), 0));

    for (int i = 1; i <= N; i++) {
        for (int h = 0; h < v.size(); h++) {
            dp[i][h] = 1 + dp[i - 1][find(A[i - 1])];

        }
    }
}