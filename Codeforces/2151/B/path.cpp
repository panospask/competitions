#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, M;
vector<long long> A;
vector<int> s;

set<int> ans;

void solve(void) {
    scanf("%d %d", &N, &M);

    A.resize(M);
    s.resize(N);

    int before_skip = N;
    for (int i = 0; i < N; i++) {
        char c;
        scanf(" %c", &c);
        s[i] = c - 'A';

        if (s[i]) {
            before_skip = min(before_skip, i);
        }
    }
    ans.clear();
    for (int i = 0; i < M; i++) {
        scanf("%lld", &A[i]);
        ans.insert(A[i]);
    }

    sort(A.begin(), A.end());
    A.pb(1e18 + 1);

    // cur is current cell
    int cur = 1;
    
    int p = 0;

    for (int i = 0; i < N; i++) {
        while (A[p] <= cur) {
            p++;
        }
        if (s[i] == 0) {
            cur++;
            // Color this
            ans.insert(cur);
        }
        else {
            // Find next empty
            cur++;
            while (A[p] == cur) {
                p++;
                cur++;
            }
            // Color it
            ans.insert(cur);
            // And find next destination
            cur++;
            while (A[p] == cur) {
                p++;
                cur++;
            }
        }
    }

    printf("%d\n", (int)ans.size());
    for (auto i : ans) {
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

    return 0;
}