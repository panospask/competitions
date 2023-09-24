#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> s, e;

void solve(void)
{
    scanf("%d", &N);

    int t_w, t_e;
    scanf("%d %d", &t_w, &t_e);

    bool bad = false;
    for (int i = 0; i < N - 1; i++) {
        int w, e;
        scanf("%d %d", &w, &e);

        if (w >= t_w && e >= t_e) {
            bad = true;
        }
    }

    if (bad)
        printf("-1");
    else
        printf("%d", t_w);
    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}