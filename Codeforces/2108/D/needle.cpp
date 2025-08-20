#include <bits/stdc++.h>

using namespace std;

int N, K;

vector<int> ans;
vector<int> ans2;

int ask(int pos) {
    printf("? %d\n", pos + 1);
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}

void solve(void) {
    scanf("%d %d", &N, &K);
    ans.resize(K);
    ans2.resize(K);

    if (N == 2 * K) {
        printf("! %d %d\n", K, K);
        fflush(stdout);
        return;
    }

    for (int i = 0; i < K; i++) {
        ans[i] = ask(i);
    }
    int idx = -1;
    for (int i = N - K; i < N; i++) {
        ans2[i % K] = ask(i);
        if (ans[i % K] != ans2[i % K]) {
            if (idx == -1) {
                idx = i % K;
            }
        }
    }
    if (idx == -1) {
        printf("! -1\n");
        fflush(stdout);
        return;
    }

    int l = 0;
    int r = (N - idx - 1) / K + 1;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (ask(idx + mid * K) == ans[idx]) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    int pos = min(idx + r * K, N - K);
    bool m1 = false;
    int res = -1;
    for (int i = pos - 1; i >= 0; i--) {
        int v = ask(i);
        if (v != ans2[i % K] || (i < K)) {
            if (!m1) {
                res = i + 1;
            }
            break;
        }
        m1 = (v == ans[i % K]);
    }


    printf("! ");
    if (res == -1) {
        printf("-1\n");
    }
    else {
        printf("%d %d\n", res, N - res);
    }
    fflush(stdout);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}