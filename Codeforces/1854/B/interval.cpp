#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll N;

void solve(void)
{
    scanf("%lld", &N);

    int l = 1;
    int r = 2;
    while (N % r == 0)
        r++;

    printf("%d\n", r - l);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();
}