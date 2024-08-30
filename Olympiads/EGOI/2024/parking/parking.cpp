#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 8;

int N;
vector<int> x;
vector<int> y;

int main(void)
{
    scanf("%d", &N);

    x.resize(N);
    y.resize(N);

    int seats = 0;
    int people = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
        seats += x[i];
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &y[i]);
        people += y[i];
    }

    int p = N - 1;
    while (seats > people) {
        int rem = min(x[p], seats - people);

        seats -= rem;
        x[p] -= rem;
        p--;
    }

    // Now we have to assign seats to people
    int shiftable = 0;
    p = 0;
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int U = 0, N = 0, D = 0;

        while (p < i && y[i]) {
            int rem = min(y[i], x[p]);

            U += rem;
            y[i] -= rem;
            x[p] -= rem;

            if (!x[p]) {
                p++;
            }
        }

        if (y[i]) {
            // Use the available shift options
            int rem = min(y[i], shiftable);

            y[i] -= rem;
            shiftable -= rem;

            if (y[i]) {
                int rem = min(x[p], y[i]);
                x[p] -= rem;
                y[i] -= rem;

                shiftable = rem;

                D = y[i];
            }
        }

        ans += U - D;
    }

    printf("%d\n", ans);

    return 0;
}