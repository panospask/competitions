#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXA = 1e5;

int N, M;
vector<int> a;
vector<int> cnt;
vector<vector<int>> factors;

int rem, ans;

void precalc(void)
{
    factors.resize(MAXA + 1);
    for (int i = 1; i <= MAXA; i++)
        for (int j = i; j <= MAXA; j += i)
            factors[j].pb(i);
}

void advance(int i, int mod)
{
    for (auto f : factors[a[i]]) {
        if (f > M)
            break;

        if (cnt[f] == 0)
            rem--;

        cnt[f] += mod;

        if (cnt[f] == 0)
            rem++;
    }
}

void solve(void)
{
    scanf("%d %d", &N, &M);

    cnt.assign(M + 1, 0);
    a.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());

    rem = M;
    ans = INT_MAX;
    int r = 0;

    for (int l = 0; l < N; l++) {
        if (l != 0) {
            advance(l - 1, -1);
        }

        while (r < N && rem) {
            advance(r, 1);
            r++;
        }
        if (rem) {
            break;
        }

        ans = min(ans, a[r-1] - a[l]);
    }

    printf("%d\n", ans != INT_MAX ? ans : -1);

    return;
}

int main(void)
{
    precalc();

    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}
