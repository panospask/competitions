#include <bits/stdc++.h>
#define MAXN 200000

using namespace std;

int arr[MAXN];
int sortarr[MAXN];
int n, x;
pair<int, int> ansval = make_pair(0, 0);
pair<int, int> ans;

int main(void)
{
    scanf("%d %d", &n, &x);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sortarr[i] = arr[i];
    }

    sort(sortarr, sortarr + n);

    int l = 0, r = n - 1;
    bool found = false;
    while (l < r) {
        while (sortarr[l] + sortarr[r] > x)
            r--;

        if (!(l < r)) break;

        if (sortarr[l] + sortarr[r] == x) {
            found = true;
            ansval = make_pair(sortarr[l], sortarr[r]);
        }

        l++;
    }

    // Transform back
    for (int i = 0; i < n && found; i++) {
        if (arr[i] == ansval.first && ans.first == 0)
            ans.first = i + 1;
        else if (arr[i] == ansval.second)
            ans.second = i + 1;
    }

    if (found)
        printf("%d %d\n", ans.first, ans.second);
    else 
        printf("IMPOSSIBLE\n");

    return 0;
}