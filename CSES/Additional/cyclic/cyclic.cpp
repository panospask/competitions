#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
ll k;
ll sum;
vector<int> a;
vector<vector<ll>> nxt;
vector<vector<ll>> len;

// Returns the number of elements contained withing the first k subarrays from x
ll elemens_contained(int x, int k)
{
    ll elem = 0;
    for (int i = 0; i < 20; i++)
        if (k & (1<<i)) {
            elem += len[i][x];
            x = nxt[i][x];
        }

    return elem;
}

// Checks if x subarrays are enough
bool check(int x)
{
    for (int i = 0; i < n; i++)
        if (elemens_contained(i, x) >= n)
            return true;

    return false;
}

int main(void)
{
    scanf("%d %lld", &n, &k);
    a.resize(n);
    nxt.resize(20, vector<ll>(n));
    len.resize(20, vector<ll>(n));
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    if (sum <= k) {
        printf("1\n");
        return 0;
    }

    sum = 0;
    int r = 0;
    // If the subarray started at l, where would it end?
    for (int l = 0; l < n; l++) {
        while (sum + a[r % n] <= k) {
            sum += a[r % n];
            r++;
        }

        nxt[0][l] = r % n;
        len[0][l] = r - l;

        sum -=a[l];
    }
    // Do the binary lifting
    for (int up = 1; up < 20; up++)
        for (int i = 0; i < n; i++) {
            nxt[up][i] = nxt[up-1][nxt[up-1][i]];
            len[up][i] = len[up-1][nxt[up-1][i]] + len[up-1][i];
        }

    int l = 1;
    r = n;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (check(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);
    return 0;
}