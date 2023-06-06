#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> a;
vector<int> low_diff;
vector<int> diff;

bool exists_leq(int x)
{
    diff[0] = low_diff[0] = 0;

    for (int i = 1; i <= n; i++) {
        diff[i] = diff[i - 1];
        if (a[i - 1] >= x)
            diff[i]++;
        else
            diff[i]--;

        low_diff[i] = min(diff[i], low_diff[i - 1]);
    }

    for (int i = k; i <= n; i++) {
        if (diff[i] - low_diff[i - k] > 0)
            return true;
    }

    return false;
}

int main(void)
{
    scanf("%d %d", &n, &k);

    a.resize(n);
    diff.resize(n + 1);
    low_diff.resize(n + 1);
    

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int l = 1;
    int r = n + 1;

    while (r > l + 1) {
        int mid = (r + l) / 2;
        if (exists_leq(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%d\n", l);
    return 0;
}