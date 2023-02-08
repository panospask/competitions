#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

ii cows[MAXN];
int n;

int main(void)
{
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &cows[i].second, &cows[i].first);

    sort(cows, cows + n);

    int l = 0, r = n - 1;
    int to_remove;
    int max_time = 0;
    while (l <= r) {
        to_remove = min(cows[l].second, cows[r].second);

        cows[l].second -= to_remove;
        cows[r].second -= to_remove;
        max_time = max(max_time, cows[l].first + cows[r].first);

        if (cows[l].second <= 0)
            l++;
        if (cows[r].second <= 0)
            r--;
    }

    printf("%d\n", max_time);
    return 0;
}