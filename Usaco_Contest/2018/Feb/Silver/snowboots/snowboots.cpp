#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int N, B;
vector<int> s, d;
vector<int> f;
vector<int> reach;

int main(void)
{
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    scanf("%d %d", &N, &B);

    f.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &f[i]);
    }

    s.resize(B);
    d.resize(B);
    for (int i = 0; i < B; i++) {
        scanf("%d %d", &s[i], &d[i]);
    }

    reach.assign(B, 0);

    int ans = INT_MAX;
    for (int t = 0; t < N; t++) {
        bool reached_tile = false;
        for (int i = 0; i < B; i++) {
            if (f[t] > s[i]) {
                continue;
            }
            if (reach[i] >= t) {
                reached_tile = true;
            }
            if (!reached_tile) {
                continue;
            }

            if (t == N - 1) {
                ans = min(ans, i);
            }

            reach[i] = t + d[i];
        }
    }

    printf("%d\n", ans);

    return 0;
}