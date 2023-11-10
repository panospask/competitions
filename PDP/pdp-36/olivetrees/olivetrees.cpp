/* USER: pask
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

    open.resize(M);

    for (int i = 0; i < M; i++) {
        int T;
        scanf("%d", &T);
        open[i] = N - T;
    }

    stack<int> s;
    ans = 0;
    int least = INT_MAX;
    for (int i = 0; i < M; i++) {
        while (!s.empty() && open[s.top()] > open[i]) {
            ans = max(ans, open[s.top()] * (i - s.top()));
            s.pop();
        }

        least = min(least, open[i]);

        if (s.empty() || open[s.top()] < open[i])
            s.push(i);
    }
    ans = max(ans, open[s.top()] * (M - s.top()));
    ans = max(ans, least * M);

    printf("%d\n", ans);

    return 0;
}