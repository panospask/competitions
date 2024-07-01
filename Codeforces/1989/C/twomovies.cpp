#include <bits/stdc++.h>

using namespace std;

int N;
int r[2];
int pos, neg;
vector<int> p[2];

void solve(void)
{
    scanf("%d", &N);
    r[0] = r[1] = 0;
    pos = neg = 0;
    p[0].resize(N);
    p[1].resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[0][i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &p[1][i]);
    }

    for (int i = 0; i < N; i++) {
        int pnt = 0;

        if (p[0][i] < p[1][i]) {
            swap(p[0][i], p[1][i]);
            pnt++;
        }

        if (p[0][i] > p[1][i]) {
            r[pnt] += p[0][i];
        }
        else if (p[0][i] > 0) {
            pos++;
        }
        else if (p[0][i] < 0) {
            neg++;
        }
    }

    if (r[0] < r[1]) {
        swap(r[0], r[1]);
    }

    // Try to make equal every time
    int add = min(pos, r[0] - r[1]);
    r[1] += add;
    pos -= add;

    int rm = min(neg, r[0] - r[1]);
    r[0] -= rm;
    neg -= rm;

    // Assume they are equal
    r[1] += pos / 2;
    r[0] += pos / 2 + pos % 2;

    r[1] -= neg / 2;
    r[0] -= neg / 2 + neg % 2;

    printf("%d\n", min(r[0], r[1]));
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