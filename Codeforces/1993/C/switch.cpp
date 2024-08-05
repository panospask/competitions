#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N, K;
int maxtime = 0;
vector<int> a;
vector<pi> events;

// Calculate range that light i will be on (beginning at at maxtime and ending at maxtime + k)
pi calc_range(int i)
{
    int n = (maxtime + K - 1 - a[i]) / (2 * K);
    int time_on = a[i] + 2 * n * K;

    int time_off = time_on + K;

    return mp(max(time_on, maxtime), min(time_off, maxtime + K));
}

pi calc_intersection(pi a, pi b)
{
    return mp(max(a.first, b.first), min(a.second, b.second));
}

void solve(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);
    maxtime = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        maxtime = max(maxtime, a[i]);
    }

    // All lights must be on at some point after the placement of the latest switch
    pi range = mp(maxtime, maxtime + K);
    for (int i = 0; i < N; i++) {
        range = calc_intersection(range, calc_range(i));
        if (range.first >= range.second) {
            printf("-1\n");
            return;
        }
    }

    printf("%d\n", range.first);
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