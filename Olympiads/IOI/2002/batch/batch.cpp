#include <bits/stdc++.h>

using namespace std;

int N, S;
vector<int> f;
vector<int> t;

vector<int> dp;

long double g(int a, int b)
{
    return (dp[a] - dp[b]) / (long double)(t[a] - t[b]); 
}

int main(void)
{
    scanf("%d %d", &N, &S);

    f.resize(N + 1);
    t.resize(N + 1);
    dp.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &t[i], &f[i]);
    }
    t[N] = f[N] = dp[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        f[i] += f[i + 1];
        t[i] += t[i + 1];
    }

    deque<int> hull;
    hull.push_back(N);
    for (int i = N - 1; i >= 0; i--) {
        while (hull.size() >= 2 && g(hull[1], hull[0]) <= f[i]) {
            hull.pop_front();
        }

        dp[i] = dp[hull.front()] + (S + t[i] - t[hull.front()]) * f[i];

        while (hull.size() >= 2 && g(i, hull.back()) <= g(hull.back(), hull[hull.size() - 2])) {
            hull.pop_back();
        }
        hull.push_back(i);
    }

    printf("%d\n", dp[0]);

    return 0;
}