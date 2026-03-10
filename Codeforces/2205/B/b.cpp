#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void solve(void) {
    int N;
    scanf("%d", &N);

    int M = N;

    vector<int> p;
    vector<int> cnt;
    for (int i = 2; i * i <= N; i++) {
        if (N % i == 0) {
            p.push_back(i);
            cnt.push_back(0);
            while (N % i == 0) {
                cnt.back()++;
                N /= i;
            }
        }
    }

    if (N != 1) {
        p.push_back(N);
        cnt.push_back(1);
    }

    N = M;
    int ans = 1;
    for (int c = 0; c < p.size(); c++) {
        int times = (cnt[c] + N - 1) / N;
        while (times) {
            ans = ans * p[c];
            times--;
        }
    }

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}