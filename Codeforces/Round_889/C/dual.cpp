#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int HALF = 10;

int N;
vector<int> a;
vector<pi> op;
int maxval, minval;
int maxpos, minpos;

void solve(void)
{
    scanf("%d", &N);

    op.clear();
    a.resize(N);
    maxval = 0;

    minval = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        maxval = max(maxval, a[i]);
        if (maxval == a[i])
            maxpos = i;
        minval = min(minval, a[i]);
        if (minval == a[i])
            minpos = i;
    }

    int cnt = 0;
    if (abs(maxval) > abs(minval)) {
        op.push_back(mp(N - 1, maxpos));
        op.push_back(mp(N - 1, maxpos));
        a[N - 1] += 2 * maxval;

        for (int i = 1; i <= N - 1; i++) {
            op.push_back(mp(N - 1, N - 1));
            a[N - 1] *= 2;

            if (a[i] < a[i - 1]) {
                op.push_back(mp(i, N - 1));
                a[i] += a[N - 1];
            }
        }
    }
    else {
        op.push_back(mp(0, minpos));
        op.push_back(mp(0, minpos));
        a[0] += 2 * minval;

        for (int i = N - 2; i >=0 ; i--) {
            op.push_back(mp(0, 0));
            a[0] *= 2;

            if (a[i] > a[i + 1]) {
                op.push_back(mp(i, 0));
                a[i] += a[0];
            }
        }
    }

    printf("%d\n", (int)op.size());
    for (auto p : op)
        printf("%d %d\n", p.first + 1, p.second + 1);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}