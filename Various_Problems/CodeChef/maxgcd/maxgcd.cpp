#include <bits/stdc++.h>

using namespace std;

const int MAXE = 20;

int n;
vector<int> a;
vector<vector<int>> sparse;
vector<int> ans;

int gcd(int a, int b)
{
    if (a < b)
        swap(a, b);

    while (b) swap(b, a %= b);

    return a;
}

int subarray_gcd(int l, int r)
{
    int len = r - l + 1;

    int maxpow = 31 - __builtin_clz(len);

    return gcd(sparse[maxpow][l], sparse[maxpow][r - (1 << maxpow) + 1]);
}

int find_latest(int l, int start, int x)
{
    int r = n;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (subarray_gcd(start, mid) >= x)
            l = mid;
        else
            r = mid;
    }

    return l;
}

void solve(void)
{
    ans.clear();
    sparse.clear();

    scanf("%d", &n);

    a.resize(n);
    ans.resize(n);
    sparse.resize(MAXE, vector<int>(n));

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
        sparse[0][i] = a[i];

    for (int len = 1; len < MAXE; len++)
        for (int i = 0; i < n; i++) {
            if (i + (1 << len) > n)
                continue;

            sparse[len][i] = gcd(sparse[len - 1][i], sparse[len - 1][i + (1 << (len - 1))]);
        }

    for (int i = 0; i < n; i++) {
        // i is the starting point of the array
        // Iterate over all possible values that the gcd can take (O(sqrt(n)))

        int v = a[i];
        int pos = i;
        while (pos != n) {
            pos = find_latest(pos, i, v);
            ans[pos - i] = max(ans[pos - i], v);

            pos++;
            if (pos == n)
                break;
            v = subarray_gcd(i, pos);
        }
    }

    for (int i = n - 2; i >= 0; i--)
        ans[i] = max(ans[i], ans[i + 1]);

    for (int i = 0; i < n; i++)
        printf("%d ", ans[i]);
    printf("\n");

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