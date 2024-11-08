#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> p;

bool ask(int i, int j)
{
    printf("? %d %d\n", i, j);
    fflush(stdout);

    int ans;
    scanf("%d", &ans);

    return ans;
}

void solve(void)
{
    scanf("%d", &N);

    p.resize(N);

    p[1] = 0;

    int t = 2;
    while (ask(1, t)) {
        p[t] = 0;
        t++;
    }

    p[t] = 1;
    
    int nxt = 2;
    for (int i = t + 1; i < N; i++) {
        while (ask(i, nxt)) {
            nxt++;
        }
        p[i] = nxt;
        nxt++;
    }

    printf("! ");
    for (int i = 1; i < N; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
    fflush(stdout);
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