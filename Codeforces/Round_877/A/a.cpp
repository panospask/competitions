#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int n;
vector<int> a;

void solve(void)
{
    scanf("%d", &n);
    a.resize(n);

    int mineg = 0;
    int maxpos = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] < 0)
            mineg = min(mineg, a[i]);
        else
            maxpos = max(maxpos, a[i]);
    }

    if (mineg != 0)
        printf("%d\n", mineg);
    else
        printf("%d\n", maxpos);

    return ;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();
}