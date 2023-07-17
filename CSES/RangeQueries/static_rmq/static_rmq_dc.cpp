#include <bits/stdc++.h>

using namespace std;

int n, q;
int size_a, size_b;
vector<vector<int>> min_at;

vector<int> a;

// Process all in range [l.. r)
void div_con(int l, int r, int lev)
{
    if (l == r - 1) {
        min_at[lev][l] = a[l];
        return;
    }

    int mid = (l + r) / 2;

    min_at[lev][mid - 1] = a[mid - 1];
    for (int i = mid - 2; i >= l; i--)
        min_at[lev][i] = min(a[i], min_at[lev][i + 1]);
    min_at[lev][mid] = a[mid];
    for (int i = mid + 1; i < r; i++)
        min_at[lev][i] = min(a[i], min_at[lev][i - 1]);

    div_con(l, mid, lev + 1);
    div_con(mid, r, lev + 1);
}

int main(void)
{
    scanf("%d %d", &n, &q);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    size_a = 1;
    size_b = 0;
    while (size_a < n) {
        size_a *= 2;
        size_b++;
    }

    a.resize(size_a);
    for (int i = n; i < size_a; i++)
        a[i] = 0;

    min_at.resize(size_b + 1, vector<int>(size_a + 1));

    div_con(0, size_a, 0);

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        int diff_lev = 32 - __builtin_clz(a ^ b);
        int lev = size_b - diff_lev;

        int ans = min(min_at[lev][a], min_at[lev][b]);

        printf("%d\n", ans);
    }

    return 0;
}