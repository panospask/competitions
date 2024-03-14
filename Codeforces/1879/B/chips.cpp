#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> a, b;

void solve(void)
{
    scanf("%d", &N);

    ll a_sum = 0, b_sum = 0;
    int a_min = INT_MAX;
    int b_min = INT_MAX;

    a.resize(N);
    b.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &b[i]);

    for (int i = 0; i < N; i++) {
        a_sum += a[i], b_sum += b[i];
        a_min = min(a_min, a[i]);
        b_min = min(b_min, b[i]);
    }

    printf("%lld\n", min(a_sum + (ll)N * b_min, b_sum + (ll)N * a_min));
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}