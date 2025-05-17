#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> big;
vector<int> ans;

void solve(void) {
    scanf("%d", &N);

    big.resize(N);
    ans.resize(N);

    for (int i = 1; i < N; i++) {
        char c;
        scanf(" %c", &c);

        big[i] = (c == '>');
    }

    int bigger = N;
    int smaller = 1;
    for (int i = N - 1; i > 0; i--) {
        if (big[i]) {
            ans[i] = bigger;
            bigger--;
        }
        else {
            ans[i] = smaller;
            smaller++;
        }
    }

    ans[0] = bigger;
    for (int i = 0; i < N; i++) {
        printf("%d ", ans[i]);
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