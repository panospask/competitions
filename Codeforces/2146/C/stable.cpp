#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> s;
vector<int> ans;

void solve(void) {
    scanf("%d", &N);

    s.resize(N + 1);
    s[N] = 1;
    ans.resize(N + 1);

    bool good = true;
    int unstable = 0;
    for (int i = 0; i <=  N; i++) {
        if (i != N) {
            scanf("%1d", &s[i]);
        }

        if (s[i]) {
            if (unstable == 1) {
                good = false;
            }
            for (int j = i - 1; j >= i - unstable; j--) {
                int diff = j - (i - unstable);
                ans[i - diff - 1] = j;
            }
            ans[i] = i;
            unstable = 0;
        }
        else {
            unstable++;
        }
    }

    if (good) {
        printf("YES\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", ans[i] + 1);
        }
        printf("\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while(t--) {
        solve();
    }

    return 0;
}