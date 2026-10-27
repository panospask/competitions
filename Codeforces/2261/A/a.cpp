#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> v[2];

void solve(void) {
    scanf("%d", &N);

    v[0].clear();
    v[1].clear();

    for (int i = 0; i < N; i++) {
        int x;
        scanf("%1d", &x);

        v[x].push_back(i);
    }

    if (v[1].size() == 1) {
        printf("0\n");
    }
    else if (v[1].size() > 2) {
        printf("%d\n", v[1].back() - v[1][0]);
    }
    else {
        printf("1\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}