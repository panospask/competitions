#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N;
vector<pi> cyc;
pi start, dest;

ll calc(pi a, pi b)
{
    return (ll)(a.first - b.first) * (a.first - b.first) + (ll)(a.second - b.second) * (a.second - b.second);
}

void solve(void)
{
    scanf("%d", &N);

    cyc.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &cyc[i].first, & cyc[i].second);
    }   

    scanf("%d %d %d %d", &start.first, &start.second, &dest.first, &dest.second);

    ll cmp = calc(start, dest);

    for (int i = 0; i < N; i++) {
        if (calc(cyc[i], dest) <= cmp) {
            printf("NO\n");
            return;
        }

    }
    printf("YES\n");

    return;
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