#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int n;
int a[MAXN + 2];
int b[MAXN + 2];

int differ[MAXN + 2];

void solve(void)
{
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    pair<int, int> ans;
    int l;
    bool entered_sort = false;
    bool inc = false;
    int cur = 0;
    a[n] = b[n] = INT_MIN;
    while (cur < n) {
        if (b[cur] <= b[cur + 1] && !inc) {
            inc = true;
            l = cur;
        }
        else if (b[cur] > b[cur + 1] && inc && !entered_sort) {
            inc = false;
            if (cur - l + 1 > ans.second - ans.first + 1)
                ans = make_pair(l, cur);
            
        }
        else if (b[cur] > b[cur + 1] && entered_sort) {
            ans = make_pair(l, cur);
            break;
        }

        if (a[cur] != b[cur]) {
            // This is actually the subarray
            entered_sort = true;
        }

        cur++;
    }

    printf("%d %d\n", ans.first + 1, ans.second + 1);
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}