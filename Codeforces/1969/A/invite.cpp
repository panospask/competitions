#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> p;

void solve(void)
{
    scanf("%d", &N);

    p.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }

    for (int i = 0; i < N; i++) {
        if (p[p[i]] == i) {
            printf("2\n");
            return;
        }
    }

    printf("3\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}