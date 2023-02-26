#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n, m, c;
int t[MAXN + 5];

bool can_have_max_wait(int w)
{
    int cur_cow = 0;
    for (int bus = 0; bus < m && cur_cow < n; bus++) {
        int cows_hold = 0;
        int next_time = t[cur_cow] + w;
        while (cows_hold < c && cur_cow < n && t[cur_cow] <= next_time) {
            cur_cow++;
            cows_hold++; 
        }
    }

    return cur_cow == n;
}

int main(void)
{
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < n; i++)
        scanf("%d", &t[i]);
    sort(t, t + n);

    int l = -1; // can_have_max_wait(l) = false
    int r = t[n-1]; // can_have_max_wait(r) = true
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (can_have_max_wait(mid))
            r = mid;
        else 
            l = mid;
    }

    printf("%d\n", r);
    return 0;
}