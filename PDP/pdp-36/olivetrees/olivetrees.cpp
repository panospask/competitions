/* USER: user061.36pdp
LANG: C++
TASK: olivetrees */

#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> open;

int ans = 0;

int main(void)
{
    freopen("olivetrees.in", "r", stdin);
    freopen("olivetrees.out", "w", stdout);

    scanf("%d %d", &N, &M);

    open.resize(M + 1);

    for (int i = 1; i <= M; i++) {
        int T;
        scanf("%d", &T);
        open[i] = N - T;
    }

    open[0] = 0;
    stack<int> s;
    s.push(0);

    int ans = 0;

    for (int i = 1; i <= M; i++) {
        while (open[s.top()] > open[i]) {
            ans = max(ans, open[s.top()] * (i - s.top()));
            s.pop();
        }

        if (open[s.top()] < open[i])
            s.push(i);
    }
    while (!s.empty()) {
        ans = max(ans, open[s.top()] * (M + 1 - s.top()));
        s.pop();
    }

    printf("%d\n", ans);

    return 0;
}