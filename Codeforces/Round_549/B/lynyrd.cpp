#include <bits/stdc++.h>

using namespace std;

const int MAXLOG = 18;

int N, M, Q;
vector<int> a;
vector<int> prv;
vector<int> dp;
vector<int> ancestor[MAXLOG];
vector<int> latest;

int jump(int v, int lvl)
{
    for (int up = 0; up < MAXLOG; up++)
        if ((1 << up) & lvl)
            v = ancestor[up][v];

    return v;
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &Q);

    a.resize(M + 1);
    latest.assign(N, 0);
    prv.resize(N);
    dp.resize(M + 1);
    ancestor[0].assign(M + 1, 0);

    int p;
    scanf("%d", &p);
    p--;
    int first = p;
    for (int i = 1; i < N; i++) {
        int num;
        scanf("%d", &num);
        num--;

        prv[num] = p;
        p = num;
    }
    prv[first] = p;

    for (int i = 1; i <= M; i++) {
        scanf("%d", &a[i]);
        a[i]--;

        ancestor[0][i] = latest[prv[a[i]]];
        latest[a[i]] = i;
    }

    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(M + 1);
        for (int i = 1; i <= M; i++)
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
    }

    dp[0] = 0;
    for (int i = 1; i <= M; i++) {
        dp[i] = max(dp[i - 1], jump(i, N - 1));
    }

    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);

        if (dp[r] >= l) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");

    return 0;
}