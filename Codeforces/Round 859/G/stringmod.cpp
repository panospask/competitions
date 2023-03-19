#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n;
int a[MAXN + 2];

void solve(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    sort(a , a + n);

    bool isgood = true;
    if (a[0] != 1)
        isgood = false;

    long long int cursum = 1;
    for (int i = 1; i < n && isgood; i++) {
        if (a[i] > cursum)
            isgood = false;
        else 
            cursum += a[i];
    }

    if (isgood)
        printf("YES\n");
    else 
        printf("NO\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int i = 0; i < t; i++)
        solve();

    return 0;
}