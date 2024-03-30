#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

// Calculate how many edges we can have in a graph with N nodes, X bridges
ll calculate(int N, int X)
{
    int rem = N - X;

    return min((ll)(rem) * (rem - 1) / 2, (ll)X) + X;
}

int main(void)
{
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int N;
        scanf("%d", &N);

        int l = 0;
        int r = N - 1;

        while (l + 1< r) {
            int m1 = ((ll)l + l + r) / 3;
            int m2 = ((ll)l + r + r) / 3;
            ll c1 = calculate(N, m1);
            ll c2 = calculate(N, m2);

            if (c1 < c2) {
                l = m1 + 1;
            }
            else if (c1 > c2) {
                r = m2 - 1;
            }
            else {
                l = m1;
                r = m2;
            }
        }

        printf("%lld\n", max(calculate(N, l), calculate(N, r)));
    }

    return 0;
}