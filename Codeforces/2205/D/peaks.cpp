#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int N;
vector<int> A;

void lds(vector<int>& A, vector<int>& res) {
    vector<int> d(N, 0);

    stack<int> s;

    for (int i = 0; i < N; i++) {
        while (s.size()) {
            if (A[s.top()] < A[i]) {
                s.pop();
            }
            else {
                break;
            }
        }

        d[i] = s.size() ? d[s.top()] + 1 : 1;
        s.push(i);
    }

    res = d;
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    vector<int> d1, d2;
    lds(A, d1);
    
    reverse(A.begin(), A.end());
    lds(A, d2);
    reverse(A.begin(), A.end());
    reverse(d2.begin(), d2.end());

    int saved = 0;
    for (int i = 0; i < N; i++) {
        saved = max(saved, d1[i] + d2[i] - 1);
    }

    printf("%d\n", N - saved);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}