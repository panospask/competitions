#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50000

using namespace std;

int x[MAXN];
int n, k;

bool can_reach_w_power(int r)
{
    int cows_rem = k;
    int cur_x = 0;
    for (int i = 0; cur_x < n && i < cows_rem; i++) {
        long long int reach = (long long int)x[cur_x] + 2 * r;
        while (cur_x < n && x[cur_x] <= reach)
            cur_x++;
    }

    return cur_x == n;
}

int main(void)
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);
    sort(x, x + n);

    int l = -1; // can_reach_w_power(l) = false
    int r = x[n-1] / 2 + 1; // can_reach_w_power(r) = true
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_reach_w_power(mid))
            r = mid;
        else 
            l = mid;
    }

    printf("%d\n", r);
    return 0;
}