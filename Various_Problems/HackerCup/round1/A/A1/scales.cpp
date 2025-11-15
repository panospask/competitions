#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<int> A;

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    int ans = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        
        if (i) {
            ans = max(ans, abs(A[i] - A[i - 1]));
        }
    }

    
    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        solve();
    }
}