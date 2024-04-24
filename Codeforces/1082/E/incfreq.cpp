#include <bits/stdc++.h>

using namespace std;

const int MAXA = 5e5;

int N, C;

int found = 0;

// The gain of the optimal starting position for each value in [1, MAXA]
vector<int> opt_start;
vector<int> a;

int main(void)
{
    scanf("%d %d", &N, &C);

    opt_start.assign(MAXA + 1, 0);
    a.resize(N);
    int tot = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);

        if (a[i] == C) {
            tot++;
        }
    }

    int ans = tot;
    for (int i = 0; i < N; i++) {
        if (a[i] == C) {
            found++;
            continue;
        }

        opt_start[a[i]] = max(opt_start[a[i]], found);
        ans = max(ans, tot - found + opt_start[a[i]] + 1);

        opt_start[a[i]]++;
    }


    printf("%d\n", ans);
}