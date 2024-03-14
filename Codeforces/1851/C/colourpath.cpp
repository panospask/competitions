#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<vector<int>> by_col;
vector<int> c;
void solve(void)
{
    by_col.clear();
    scanf("%d %d", &N, &K);

    by_col.resize(N);
    c.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
        c[i]--;
        by_col[c[i]].push_back(i);
    }

    if (by_col[c[0]].size() < K || by_col[c[N- 1]].size() < K) {
        printf("NO\n");
        return;
    }

    if (c[0] == c[N - 1]) {
        printf("YES\n");
    }
    else {
        int v = by_col[c[0]][K - 1];

        int lpos = by_col[c[N - 1]].size() - K;
        int u = by_col[c[N - 1]][lpos];

        if (v < u)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}